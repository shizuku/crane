/***********************
 * @file: expr_group.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/expr_group.hpp"

namespace crane {

ExprGroup::ExprGroup(std::vector<std::shared_ptr<Expr>> list) : list(std::move(list)) {}

size_t ExprGroup::beg() const {
  if (!list.empty()) {
    return list[0]->beg();
  }
  return 0;
}
size_t ExprGroup::end() const {
  if (!list.empty()) {
    return list[list.size() - 1]->end();
  }
  return 0;
}

}// namespace crane
