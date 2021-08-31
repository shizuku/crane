/***********************
 * @file: expr.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <memory>
#include <utility>

#include "crane/codegen_visitor.hpp"
#include "crane/token.hpp"

namespace crane {

struct Expr {
  [[nodiscard]] virtual size_t beg() const = 0;
  [[nodiscard]] virtual size_t end() const = 0;

  virtual llvm::Value* codegen(CodegenVisitor* v) const = 0;

  virtual llvm::Type* typegen(CodegenVisitor* v) const = 0;
};

}// namespace crane
