/***********************
 * @file: unary_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct UnaryExpr : Expr {
  size_t pos;
  TokenKind op;
  std::shared_ptr<Expr> x;

  UnaryExpr(size_t pos, TokenKind op, std::shared_ptr<Expr> x);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
