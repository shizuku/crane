/***********************
 * @file: position.cpp
 * @author: shizuku
 * @date: 2021/7/15
 ***********************/
#include "crane/position.hpp"

namespace crane {

Position::Position(size_t line, size_t column, const std::string_view& filename)
    : filename{filename}, line{line}, column{column} {}

std::string Position::toString() const {
  if (!filename.empty()) {
    return std::string(filename) + ":" + std::to_string(line) + ":" + std::to_string(column);
  }
  return std::to_string(line) + ":" + std::to_string(column);
}

std::ostream& operator<<(std::ostream& o, const Position& p) {
  if (p.filename.empty()) {
    o << std::to_string(p.line) << std::string(":") << std::to_string(p.column);
  } else {
    o << p.filename << std::string(":") << std::to_string(p.line) << std::string(":") << std::to_string(p.column);
  }
  return o;
}

}// namespace crane
