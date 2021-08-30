/***********************
 * @file: parser.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/parser.hpp"

namespace crane {

Parser::Parser(const std::shared_ptr<File>& f) : s{f}, error{f->errorHandler} {
  next();
}

std::shared_ptr<ExprGroup> Parser::parseFile() {
  return parseExprGroup(tok_eof);
}

std::shared_ptr<ExprGroup> Parser::parseExprGroup(TokenKind end) {
  std::vector<std::shared_ptr<Expr>> list;
  while (tok.kind != end) {
    list.emplace_back(parseExpr());
    expect(tok_semicolon);
  }
  return std::make_shared<ExprGroup>(list);
}

std::shared_ptr<BlockExpr> Parser::parseBlockExpr() {
  auto lpPos = expect(tok_lbrace);
  auto x = parseExprGroup(tok_rbrace);
  auto rpPos = expect(tok_rbrace);
  return std::make_shared<BlockExpr>(lpPos, x->list, rpPos);
}

std::shared_ptr<Expr> Parser::parseExpr() {
  switch (tok.kind) {
    case tok_var:
      return parseVarDeclExpr();
    case tok_fun:
      return parseFunDeclExpr();
    case tok_return:
      return parseReturnExpr();
    default:
      return parseBinaryExpr(lowestPrec + 1);
  }
}

std::shared_ptr<Expr> Parser::parseType() {
  switch (tok.kind) {
    case tok_ident: {
      auto id = parseIdent();
      return id;
    }
    default:
      return nullptr;
  }
}

std::shared_ptr<Expr> Parser::parseVarDeclExpr() {
  auto varPos = expect(tok_var);
  auto name = parseIdent();
  std::shared_ptr<Expr> type = nullptr;
  std::shared_ptr<Expr> value = nullptr;
  if (tok.kind == tok_colon) {
    next();
    type = parseType();
  }
  if (tok.kind == tok_assign) {
    next();
    value = parseExpr();
  }
  return std::make_shared<VarDeclExpr>(varPos, name, type, value);
}

std::shared_ptr<Expr> Parser::parseFunDeclExpr() {
  auto funPos = expect(tok_fun);
  auto name = parseIdent();
  auto params = parseParameterList();
  std::shared_ptr<Expr> result = nullptr;
  if (tok.kind == tok_colon) {
    next();
    result = parseType();
  }
  auto type = std::make_shared<FunType>(funPos, params, result);
  std::shared_ptr<Expr> body;
  if (tok.kind == tok_assign) {
    next();
    body = parseExpr();
  } else {
    body = parseBlockExpr();
  }
  return std::make_shared<FunDeclExpr>(name, type, body);
}

std::shared_ptr<Expr> Parser::parseReturnExpr() {
  auto returnPos = expect(tok_return);
  auto x = parseExpr();
  return std::make_shared<ReturnExpr>(returnPos, x);
}

std::shared_ptr<FieldList> Parser::parseParameterList() {
  auto lpPos = expect(tok_lparen);
  std::vector<std::shared_ptr<Field>> list;
  while (tok.kind != tok_rparen && tok.kind != tok_eof) {
    list.push_back(parseParameter());
    if (tok.kind == tok_rparen) break;
    expect(tok_comma);
  }
  auto rpPos = expect(tok_rparen);
  return std::make_shared<FieldList>(lpPos, list, rpPos);
}

std::shared_ptr<Field> Parser::parseParameter() {
  auto name = parseIdent();
  expect(tok_colon);
  auto type = parseType();
  return std::make_shared<Field>(name, type);
}

std::shared_ptr<FieldList> Parser::parseFieldList() {
  if (tok.kind == tok_lparen) {
    return parseFieldList(tok_lparen, tok_rparen);
  }
  if (tok.kind == tok_lbrace) {
    return parseFieldList(tok_lbrace, tok_rbrace);
  }
  return nullptr;
}

std::shared_ptr<FieldList> Parser::parseFieldList(TokenKind openingKind, TokenKind closingKind) {
  auto opening = expect(openingKind);
  std::vector<std::shared_ptr<Field>> list;
  while (tok.kind != closingKind) {
    list.push_back(parseField());
    if (tok.kind == tok_comma) {
      next();
    }
  }
  auto closing = expect(closingKind);
  return std::make_shared<FieldList>(opening, list, closing);
}

std::shared_ptr<Field> Parser::parseField() {
  auto name = parseIdent();
  expect(tok_colon);
  auto type = parseExpr();
  return std::make_shared<Field>(name, type);
}

std::shared_ptr<Expr> Parser::parseBinaryExpr(int prec) {
  auto x = parseUnaryExpr();
  for (;;) {
    auto pr = tokPrec(tok.kind);
    if (pr < prec) {
      return x;
    }
    auto op = tok;
    auto pos = expect(op.kind);
    auto y = parseBinaryExpr(pr + 1);
    x = std::make_shared<BinaryExpr>(x, pos, op.kind, y);
  }
}

std::shared_ptr<Expr> Parser::parseUnaryExpr() {
  switch (tok.kind) {
    case tok_add:
    case tok_sub: {
      Token op = tok;
      next();
      auto x = parseUnaryExpr();
      return std::make_shared<UnaryExpr>(op.pos, op.kind, std::move(x));
    }
    default:
      break;
  }
  return parsePrimaryExpr();
}

std::shared_ptr<Expr> Parser::parsePrimaryExpr() {
  auto x = parseOperand();
  for (;;) {
    switch (tok.kind) {
      case tok_lparen:
        x = parseCallOrConversion(x);
      default:
        return x;
    }
  }
}

std::shared_ptr<Expr> Parser::parseOperand() {
  switch (tok.kind) {
    case tok_ident:
      return parseIdent();
    case tok_int:
    case tok_float: {
      auto x = std::make_shared<BasicLit>(tok.kind, tok.pos, tok.lit);
      next();
      return x;
    }
    case tok_lparen: {
      auto lparenPos = expect(tok_lparen);
      auto x = parseExpr();
      auto rparenPos = expect(tok_rparen);
      return std::make_shared<ParenExpr>(lparenPos, x, rparenPos);
    }
    default:
      auto pos = tok.pos;
      errorExpected(pos, "operand");
      return std::make_shared<BadExpr>(pos, tok.pos);
  }
}

std::shared_ptr<Expr> Parser::parseLhs() {
  auto x = parseExpr();
  return x;
}

std::shared_ptr<Expr> Parser::parseRhs() {
  auto x = parseExpr();
  return x;
}

std::shared_ptr<Expr> Parser::parseCallOrConversion(const std::shared_ptr<Expr>& fun) {
  auto lparenPos = expect(tok_lparen);
  std::vector<std::shared_ptr<Expr>> args;
  while (tok.kind != tok_rparen && tok.kind != tok_eof) {
    args.push_back(parseExpr());
    if (tok.kind == tok_comma) {
      expect(tok_comma);
    }
  }
  auto rparenPos = expect(tok_rparen);
  return std::make_shared<CallExpr>(fun, lparenPos, args, rparenPos);
}

std::shared_ptr<Ident> Parser::parseIdent() {
  if (tok.kind == tok_ident) {
    auto r = std::make_shared<Ident>(tok.pos, tok.lit);
    next();
    return r;
  }
  expect(tok_ident);
  return nullptr;
}

void Parser::next() { tok = s.scan(); }

void Parser::errorExpected(size_t pos, const std::string& msg) const {
  auto rm = msg;
  if (pos == tok.pos) {
    rm += "found, '" + tok.toString() + "'";
  }
  error(pos, rm);
}

size_t Parser::expect(const TokenKind& tp) {
  auto p = tok.pos;
  if (tok.kind != tp) {
    error(tok.pos, "expect '" + std::string(to_string(tp)) +
                       "', found '" + std::string(to_string(tok.kind)) + "'");
  }
  next();
  return p;
}

}// namespace crane
