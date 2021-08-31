/***********************
 * @file: call_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/call_expr.hpp"

namespace crane {

CallExpr::CallExpr(std::shared_ptr<Expr> fun, size_t lparenPos, std::vector<std::shared_ptr<Expr>> args, size_t rparenPos)
    : fun(std::move(fun)), lparenPos(lparenPos), args(std::move(args)), rparenPos(rparenPos) {}

size_t CallExpr::beg() const {
  return fun->beg();
}

size_t CallExpr::end() const {
  return rparenPos;
}

llvm::Value* CallExpr::codegen(CodegenVisitor* v) const {
  return v->codegenCallExpr(*this);
}

}// namespace crane
