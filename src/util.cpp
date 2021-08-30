/***********************
 * @file: util.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/util.hpp"

namespace crane {

std::string readFile(const std::string& fn) {
  std::ifstream i{fn};
  std::stringstream r{};
  char c;
  while (!i.eof()) {
    i.get(c);
    r << c;
  }
  return r.str();
}

std::string getFileName(const std::string& filePath) {
  auto div = '/';
  auto p = filePath.find_last_of(div);
  if (p == std::string::npos) {
    return filePath;
  }
  return filePath.substr(p + 1);
}

}// namespace crane
