/***********************
 * @file: binary_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/binary_expr.hpp"

namespace crane {

BinaryExpr::BinaryExpr(std::shared_ptr<Expr> x, size_t opPos, TokenKind kind, std::shared_ptr<Expr> y)
    : x(std::move(x)), opPos(opPos), kind(kind), y(std::move(y)) {}

size_t BinaryExpr::beg() const {
  return x->beg();
}

size_t BinaryExpr::end() const {
  return y->end();
}

llvm::Value* BinaryExpr::codegen(CodegenVisitor* v) const {
  return v->codegenBinaryExpr(*this);
}

}// namespace crane
