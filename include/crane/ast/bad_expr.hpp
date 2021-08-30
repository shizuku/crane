/***********************
 * @file: bad_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct BadExpr : Expr {
  size_t from;
  size_t to;

  BadExpr(size_t from, size_t to);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
