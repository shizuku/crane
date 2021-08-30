/***********************
 * @file: fun_decl_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "crane/ast/field_list.hpp"
#include "decl_expr.hpp"

namespace crane {

struct FunType {
  size_t funPos;
  std::shared_ptr<FieldList> params;
  std::shared_ptr<Expr> result;

  FunType(size_t funPos, std::shared_ptr<FieldList> params, std::shared_ptr<Expr> result);
};

struct FunDeclExpr : DeclExpr {
  std::shared_ptr<Ident> name;
  std::shared_ptr<FunType> type;
  std::shared_ptr<Expr> body;

  FunDeclExpr(std::shared_ptr<Ident> name, std::shared_ptr<FunType> type, std::shared_ptr<Expr> body);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
