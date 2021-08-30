/***********************
 * @file: basic_lit.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"

namespace crane {

struct BasicLit : Expr {
  TokenKind kind;
  size_t pos;
  std::string lit;

  BasicLit(TokenKind kind, size_t pos, std::string lit);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
