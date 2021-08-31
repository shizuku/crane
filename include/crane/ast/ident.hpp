/***********************
 * @file: ident.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct Ident : Expr {
  size_t pos;
  std::string name;

  Ident(size_t pos, std::string name);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
