/***********************
 * @file: parser.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include "crane/ast/bad_expr.hpp"
#include "crane/ast/basic_lit.hpp"
#include "crane/ast/binary_expr.hpp"
#include "crane/ast/block_expr.hpp"
#include "crane/ast/call_expr.hpp"
#include "crane/ast/decl/fun_decl_expr.hpp"
#include "crane/ast/decl/var_decl_expr.hpp"
#include "crane/ast/expr_group.hpp"
#include "crane/ast/ident.hpp"
#include "crane/ast/paren_expr.hpp"
#include "crane/ast/return_expr.hpp"
#include "crane/ast/unary_expr.hpp"
#include "crane/error.hpp"
#include "crane/file.hpp"
#include "crane/scanner.hpp"
#include "crane/token.hpp"

namespace crane {

class Parser {
public:
  Parser() = delete;

  explicit Parser(const std::shared_ptr<File>& f);

public:
  std::shared_ptr<ExprGroup> parseFile();

  std::shared_ptr<ExprGroup> parseExprGroup(TokenKind end);

  std::shared_ptr<BlockExpr> parseBlockExpr();

  std::shared_ptr<Ident> parseIdent();

  std::shared_ptr<Expr> parseExpr();

  std::shared_ptr<Expr> parseType();
  std::shared_ptr<Expr> parseLhs();
  std::shared_ptr<Expr> parseRhs();

  std::shared_ptr<Expr> parseVarDeclExpr();
  std::shared_ptr<Expr> parseFunDeclExpr();

  std::shared_ptr<Expr> parseReturnExpr();

  std::shared_ptr<FieldList> parseParameterList();
  std::shared_ptr<Field> parseParameter();

  std::shared_ptr<FieldList> parseFieldList();
  std::shared_ptr<FieldList> parseFieldList(TokenKind opening, TokenKind closing);
  std::shared_ptr<Field> parseField();

  std::shared_ptr<Expr> parseBinaryExpr(int prec);
  std::shared_ptr<Expr> parseUnaryExpr();
  std::shared_ptr<Expr> parsePrimaryExpr();
  std::shared_ptr<Expr> parseOperand();

  std::shared_ptr<Expr> parseCallOrConversion(const std::shared_ptr<Expr>& fun);

private:
  void next();
  void errorExpected(size_t pos, const std::string& msg) const;
  size_t expect(const TokenKind& tp);

private:
  Scanner s;
  Token tok;
  ErrorHandler error;
};

}// namespace crane
