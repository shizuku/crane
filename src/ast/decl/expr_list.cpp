/***********************
 * @file: expr_list.cpp
 * @author: shizuku
 * @date: 2021/8/30
 ***********************/
#include "crane/ast/expr_list.hpp"

namespace crane {

ExprList::ExprList(std::vector<std::shared_ptr<Expr>> list) : list(std::move(list)) {}

size_t ExprList::beg() const {
  if (!list.empty()) {
    return list[0]->beg();
  }
  return 0;
}

size_t ExprList::end() const {
  if (!list.empty()) {
    return list[list.size() - 1]->end();
  }
  return 0;
}

llvm::Value* ExprList::codegen(CodegenVisitor* v) const {
  return v->codegenExprList(*this);
}

}// namespace crane
