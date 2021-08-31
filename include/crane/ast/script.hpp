/***********************
 * @file: script.hpp
 * @author: shizuku
 * @date: 2021/8/30
 ***********************/
#pragma once

#include "crane/ast/expr.hpp"
#include "crane/ast/expr_group.hpp"

namespace crane {

struct ScriptFile : Expr {
  std::shared_ptr<ExprGroup> group;

  explicit ScriptFile(std::shared_ptr<ExprGroup> group);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
