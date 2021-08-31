/***********************
 * @file: val_decl_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "crane/ast/expr.hpp"
#include "crane/ast/ident.hpp"

namespace crane {

struct ValDeclExpr : Expr {
  size_t valPos;
  std::shared_ptr<Ident> name;
  std::shared_ptr<Expr> type;
  std::shared_ptr<Expr> value;

  ValDeclExpr(size_t valPos, std::shared_ptr<Ident> name, std::shared_ptr<Expr> type, std::shared_ptr<Expr> value);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
