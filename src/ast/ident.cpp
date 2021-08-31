/***********************
 * @file: ident.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/ident.hpp"

namespace crane {

Ident::Ident(size_t pos, std::string name) : pos(pos), name(std::move(name)) {}

size_t Ident::beg() const {
  return pos;
}

size_t Ident::end() const {
  return pos + name.size();
}

llvm::Value* Ident::codegen(CodegenVisitor* v) const {
  return v->codegenIdent(*this);
}

}// namespace crane
