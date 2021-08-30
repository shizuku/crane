/***********************
 * @file: util.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <fstream>
#include <sstream>
#include <string>

namespace crane {

std::string readFile(const std::string& fn);

std::string getFileName(const std::string& filePath);

}// namespace crane
