/***********************
 * @file: field_list.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/ast/field_list.hpp"

namespace crane {

Field::Field(std::shared_ptr<Ident> name, std::shared_ptr<Expr> type)
    : name(std::move(name)), type(std::move(type)) {}

size_t Field::beg() const {
  return name->beg();
}

size_t Field::end() const {
  return type->end();
}

llvm::Value* Field::codegen(CodegenVisitor* v) const {
  return nullptr;
}

FieldList::FieldList(size_t opening, std::vector<std::shared_ptr<Field>> list, size_t closing)
    : opening(opening), list(std::move(list)), closing(closing) {}

size_t FieldList::beg() const {
  return opening;
}

size_t FieldList::end() const {
  return closing;
}

llvm::Value* FieldList::codegen(CodegenVisitor* v) const {
  return v->codegenFieldList(*this);
}

}// namespace crane
