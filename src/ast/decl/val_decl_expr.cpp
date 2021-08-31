/***********************
 * @file: val_decl_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/decl/val_decl_expr.hpp"

namespace crane {

ValDeclExpr::ValDeclExpr(size_t valPos, std::shared_ptr<Ident> name, std::shared_ptr<Expr> type, std::shared_ptr<Expr> value)
    : valPos(valPos), name(std::move(name)), type(std::move(type)), value(std::move(value)) {}

size_t ValDeclExpr::beg() const {
  return valPos;
}

size_t ValDeclExpr::end() const {
  if (value) {
    return value->end();
  }
  if (type) {
    return type->end();
  }
  return name->end();
}

llvm::Value* ValDeclExpr::codegen(CodegenVisitor* v) const {
  return v->codegenValDeclExpr(*this);
}

}// namespace crane
