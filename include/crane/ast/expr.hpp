/***********************
 * @file: expr.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <memory>
#include <utility>

#include "crane/token.hpp"

namespace crane {

struct Expr {
  [[nodiscard]] virtual size_t beg() const = 0;
  [[nodiscard]] virtual size_t end() const = 0;
};

}// namespace crane
