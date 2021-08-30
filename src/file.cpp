/***********************
 * @file: file.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/file.hpp"

namespace crane {

File::File(std::string_view name, const std::string& content)
    : content{std::make_shared<std::string>(content)}, name{name} {}

Position File::getPosition(size_t pos) const {
  pos += 1;
  size_t line = 1;
  size_t column = pos;
  for (auto& i : lines) {
    if (i <= pos) {
      column = pos - i;
      line++;
    } else {
      break;
    }
  }
  return {line, column, name};
}

std::string File::range(size_t beg, size_t end) const {
  return "<" + getPosition(beg).toString() + ", " + getPosition(end).toString() + ">";
}

std::string File::range(const std::shared_ptr<Expr>& expr) const {
  return range(expr->beg(), expr->end());
}

void File::printError(std::ostream& o, const Error& e) const {
  o << getPosition(e.pos) << std::string("\t") << e.msg;
}

}// namespace crane
