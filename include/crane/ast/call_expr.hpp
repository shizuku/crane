/***********************
 * @file: call_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct CallExpr : Expr {
  std::shared_ptr<Expr> fun;
  size_t lparenPos;
  std::vector<std::shared_ptr<Expr>> args;
  size_t rparenPos;

  CallExpr(std::shared_ptr<Expr> fun, size_t lparenPos, std::vector<std::shared_ptr<Expr>> args, size_t rparenPos);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
