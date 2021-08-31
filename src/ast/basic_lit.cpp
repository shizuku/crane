/***********************
 * @file: basic_lit.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/basic_lit.hpp"

namespace crane {

BasicLit::BasicLit(TokenKind kind, size_t pos, std::string lit)
    : kind(kind), pos(pos), lit(std::move(lit)) {}

size_t BasicLit::beg() const {
  return pos;
}

size_t BasicLit::end() const {
  return pos + lit.size();
}

llvm::Value* BasicLit::codegen(CodegenVisitor* v) const {
  return v->codegenBasicLit(*this);
}

}// namespace crane
