/***********************
 * @file: bad_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/bad_expr.hpp"

namespace crane {

BadExpr::BadExpr(size_t from, size_t to) : from(from), to(to) {}

size_t BadExpr::beg() const {
  return from;
}

size_t BadExpr::end() const {
  return to;
}

llvm::Value* BadExpr::codegen(CodegenVisitor* v) const {
  return v->codegenBadExpr(*this);
}

llvm::Type* BadExpr::typegen(CodegenVisitor* v) const {
  return nullptr;
}

}// namespace crane
