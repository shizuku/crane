/***********************
 * @file: file.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <functional>
#include <memory>
#include <utility>

#include "crane/ast/expr.hpp"
#include "crane/error.hpp"
#include "crane/position.hpp"

namespace crane {

class File {
public:
  File(std::string_view name, const std::string& content);

public:
  [[nodiscard]] Position getPosition(size_t pos) const;

  [[nodiscard]] std::string range(size_t beg, size_t end) const;

  [[nodiscard]] std::string range(const std::shared_ptr<Expr>& expr) const;

  void printError(std::ostream& o, const Error& e) const;

public:
  std::vector<Error> errors{};
  ErrorHandler errorHandler = [&](size_t pos, std::string msg) {
    errors.emplace_back(Error{pos, std::move(msg)});
  };

public:
  std::vector<size_t> lines{};
  std::function<void(size_t)> addLine = [&](size_t pos) { lines.push_back(pos); };

public:
  std::string_view name;
  std::shared_ptr<std::string> content;
};

}// namespace crane
