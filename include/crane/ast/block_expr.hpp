/***********************
 * @file: block_expr.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct BlockExpr : Expr {
  size_t opening;
  std::vector<std::shared_ptr<Expr>> list;
  size_t closing;

  BlockExpr(size_t opening, std::vector<std::shared_ptr<Expr>> list, size_t closing);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value * codegen(CodegenVisitor *v) const override;
};

}// namespace crane
