/***********************
 * @file: paren_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct ParenExpr : Expr {
  size_t lparenPos;
  std::shared_ptr<Expr> x;
  size_t rparenPos;

  ParenExpr(size_t lparenPos, std::shared_ptr<Expr> x, size_t rparenPos);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
