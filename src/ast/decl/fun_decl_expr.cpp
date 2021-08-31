/***********************
 * @file: fun_decl_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/decl/fun_decl_expr.hpp"

namespace crane {

FunType::FunType(size_t funPos, std::shared_ptr<FieldList> params, std::shared_ptr<Expr> result)
    : funPos(funPos), params(std::move(params)), result(std::move(result)) {}

FunDeclExpr::FunDeclExpr(std::shared_ptr<Ident> name, std::shared_ptr<FunType> type, std::shared_ptr<Expr> body)
    : name(std::move(name)), type(std::move(type)), body(std::move(body)) {}

size_t FunDeclExpr::beg() const {
  return type->funPos;
}

size_t FunDeclExpr::end() const {
  return body->end();
}

llvm::Value* FunDeclExpr::codegen(CodegenVisitor* v) const {
  return v->codegenFunDeclExpr(*this);
}

}// namespace crane
