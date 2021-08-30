/***********************
 * @file: return_expr.cpp
 * @author: shizuku
 * @date: 2021/7/14
 ***********************/
#include "crane/ast/return_expr.hpp"

namespace crane {

ReturnExpr::ReturnExpr(size_t returnPos, std::shared_ptr<Expr> result)
    : returnPos(returnPos), result(std::move(result)) {}

size_t ReturnExpr::beg() const {
  return returnPos;
}

size_t ReturnExpr::end() const {
  return result->end();
}

}// namespace crane
