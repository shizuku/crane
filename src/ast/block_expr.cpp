/***********************
 * @file: block_expr.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/block_expr.hpp"

namespace crane {

BlockExpr::BlockExpr(size_t opening, std::vector<std::shared_ptr<Expr>> list, size_t closing)
    : opening(opening), list(std::move(list)), closing(closing) {}

size_t BlockExpr::beg() const {
  return opening;
}

size_t BlockExpr::end() const {
  return closing;
}

llvm::Value* BlockExpr::codegen(CodegenVisitor* v) const {
  return v->codegenBlockExpr(*this);
}

}// namespace crane
