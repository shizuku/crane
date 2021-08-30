/***********************
 * @file: return_expr.hpp
 * @author: shizuku
 * @date: 2021/7/14
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct ReturnExpr : Expr {
  size_t returnPos;
  std::shared_ptr<Expr> result;

  ReturnExpr(size_t returnPos, std::shared_ptr<Expr> result);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
