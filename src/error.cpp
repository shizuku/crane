/***********************
 * @file: error.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/error.hpp"

namespace crane {

Error::Error(size_t pos, std::string msg) : pos{pos}, msg{std::move(msg)} {}

}// namespace crane
