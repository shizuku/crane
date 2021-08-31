/***********************
 * @file: paren_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/paren_expr.hpp"

namespace crane {

ParenExpr::ParenExpr(size_t lparenPos, std::shared_ptr<Expr> x, size_t rparenPos)
    : lparenPos(lparenPos), x(std::move(x)), rparenPos(rparenPos) {}

size_t ParenExpr::beg() const {
  return lparenPos;
}

size_t ParenExpr::end() const {
  return rparenPos;
}

llvm::Value* ParenExpr::codegen(CodegenVisitor* v) const {
  return v->codegenParenExpr(*this);
}

}// namespace crane
