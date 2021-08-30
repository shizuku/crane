/***********************
* @file: main.cpp
* @author: shizuku
* @date: 2021/7/12
***********************/
#include <iostream>

#include "crane/file.hpp"
#include "crane/parser.hpp"
#include "crane/util.hpp"

using namespace crane;

int testScan() {
  std::string filePath = "../../op.cn";
  auto fileName = getFileName(filePath);
  auto file = std::make_shared<File>(fileName, readFile(filePath));

  Scanner s{file};
  for (;;) {
    auto tok = s.scan();
    std::cout << tok << std::endl;
    if (tok.kind == tok_eof) break;
  }
  return 0;
}

int testParse() {
  std::string filePath = "../../a.cn";
  auto fileName = getFileName(filePath);
  auto file = std::make_shared<File>(fileName, readFile(filePath));

  Parser p{file};
  auto ast = p.parseFile();
  return 0;
}

int main() {
  //  return testScan();
  return testParse();
}
