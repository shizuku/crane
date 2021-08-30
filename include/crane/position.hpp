/***********************
 * @file: position.hpp
 * @author: shizuku
 * @date: 2021/7/15
 ***********************/
#pragma once

#include "crane/token.hpp"

namespace crane {

struct Position {
  size_t line;
  size_t column;
  const std::string_view& filename;

  Position(size_t line, size_t column, const std::string_view& filename);

  [[nodiscard]] std::string toString() const;
};

std::ostream& operator<<(std::ostream& o, const Position& p);

}// namespace crane
