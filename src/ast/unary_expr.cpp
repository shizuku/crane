/***********************
 * @file: unary_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/unary_expr.hpp"

namespace crane {

UnaryExpr::UnaryExpr(size_t pos, TokenKind op, std::shared_ptr<Expr> x)
    : pos(pos), op(op), x(std::move(x)) {}

size_t UnaryExpr::beg() const {
  return pos;
}

size_t UnaryExpr::end() const {
  return x->end();
}

llvm::Value* UnaryExpr::codegen(CodegenVisitor* v) const {
  return v->codegenUnaryExpr(*this);
}

}// namespace crane
