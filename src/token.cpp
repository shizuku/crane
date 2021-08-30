/***********************
 * @file: token.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/token.hpp"

namespace crane {

Token::Token() : kind(tok_illegal), pos(), lit() {}

Token::Token(TokenKind kind, size_t pos, text_t lit) : kind(kind), pos(pos), lit(std::move(lit)) {}

bool Token::isLiteral() const {
  return kind > literal_beg && kind < literal_end;
}

bool Token::isOperator() const {
  return kind > operator_beg && kind < operator_end;
}

bool Token::isKeyword() const {
  return kind > keyword_beg && kind < keyword_end;
}

std::string Token::toString() const {
  if (isLiteral()) {
    return lit;
  } else {
    return std::string(to_string(kind));
  }
}

std::ostream& operator<<(std::ostream& o, const Token& t) {
  o << t.toString();
  return o;
}

int tokPrec(TokenKind k) {
  switch (k) {
    case tok_lor:
      return 1;
    case tok_land:
      return 2;
    case tok_eql:
    case tok_neq:
    case tok_lss:
    case tok_leq:
    case tok_gtr:
    case tok_geq:
      return 3;
    case tok_add:
    case tok_sub:
    case tok_or:
    case tok_xor:
      return 4;
    case tok_mul:
    case tok_quo:
    case tok_rem:
    case tok_shl:
    case tok_shr:
    case tok_and:
    case tok_and_not: return 5;
    default:
      return lowestPrec;
  }
}

}// namespace crane
