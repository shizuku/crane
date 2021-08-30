/***********************
 * @file: var_decl_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/decl/var_decl_expr.hpp"

namespace crane {

VarDeclExpr::VarDeclExpr(size_t varPos, std::shared_ptr<Ident> name, std::shared_ptr<Expr> type, std::shared_ptr<Expr> value)
    : varPos(varPos), name(std::move(name)), type(std::move(type)), value(std::move(value)) {}

size_t VarDeclExpr::beg() const {
  return varPos;
}

size_t VarDeclExpr::end() const {
  if (value) {
    return value->end();
  }
  if (type) {
    return type->end();
  }
  return name->end();
}

}// namespace crane
