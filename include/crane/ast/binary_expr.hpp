/***********************
 * @file: binary_expr.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct BinaryExpr : Expr {
  std::shared_ptr<Expr> x;
  size_t opPos;
  TokenKind kind;
  std::shared_ptr<Expr> y;

  BinaryExpr(std::shared_ptr<Expr> x, size_t opPos, TokenKind kind, std::shared_ptr<Expr> y);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;

  llvm::Value* codegen(CodegenVisitor* v) const override;
};

}// namespace crane
