/***********************
 * @file: error.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <functional>

#include "crane/token.hpp"

namespace crane {

struct Error {
  size_t pos;
  std::string msg;

  Error(size_t pos, std::string msg);
};

using ErrorHandler = std::function<void(size_t, std::string)>;

}// namespace crane
