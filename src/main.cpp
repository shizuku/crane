/***********************
* @file: main.cpp
* @author: shizuku
* @date: 2021/7/12
***********************/
#include <iostream>

#include <llvm/Support/FileSystem.h>

#include "crane/code_generator.hpp"
#include "crane/file.hpp"
#include "crane/parser.hpp"
#include "crane/util.hpp"

using namespace crane;

int testScan() {
  std::string filePath = "../../op.cn";
  auto fileName = getFileName(filePath);
  auto file = std::make_shared<File>(fileName, readFile(filePath));

  std::vector<Error> errors{};
  ErrorHandler error = [&](size_t pos, std::string msg) {
    errors.emplace_back(Error{pos, std::move(msg)});
  };

  Scanner s{file, error};
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

  std::vector<Error> errors{};
  ErrorHandler error = [&](size_t pos, std::string msg) {
    errors.emplace_back(Error{pos, std::move(msg)});
  };

  Parser p{file, error};
  auto ast = p.parseFile();

  CodeGenerator g{fileName, error};
  g.codegenScriptFile(*ast);
  if (!errors.empty()) {
    return 1;
  }
  std::error_code ec;
  llvm::raw_fd_ostream os(filePath + ".ll", ec, llvm::sys::fs::F_None);
  g.module->print(os, nullptr);
  os.flush();
  return 0;
}

int main() {
  //  return testScan();
  return testParse();
}
