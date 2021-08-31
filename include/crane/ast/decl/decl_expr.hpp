/***********************
 * @file: decl_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "crane/ast/expr.hpp"

namespace crane {

struct DeclExpr : Expr {
  [[nodiscard]] size_t beg() const override = 0;
  [[nodiscard]] size_t end() const override = 0;

  llvm::Value* codegen(CodegenVisitor* v) const override = 0;
};

}// namespace crane
