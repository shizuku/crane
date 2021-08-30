/***********************
 * @file: var_decl_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "crane/ast/ident.hpp"
#include "decl_expr.hpp"

namespace crane {

struct VarDeclExpr : DeclExpr {
  size_t varPos;
  std::shared_ptr<Ident> name;
  std::shared_ptr<Expr> type;
  std::shared_ptr<Expr> value;

  VarDeclExpr(size_t varPos, std::shared_ptr<Ident> name, std::shared_ptr<Expr> type, std::shared_ptr<Expr> value);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
