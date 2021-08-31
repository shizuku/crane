/***********************
 * @file: expr_list.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct ExprList : Expr {
  std::vector<std::shared_ptr<Expr>> list;

  explicit ExprList(std::vector<std::shared_ptr<Expr>> list);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
