/***********************
 * @file: script.cpp
 * @author: shizuku
 * @date: 2021/8/30
 ***********************/
#include "crane/ast/script.hpp"

namespace crane {

ScriptFile::ScriptFile(std::shared_ptr<ExprGroup> group) : group(std::move(group)) {}

size_t ScriptFile::beg() const { return group->beg(); }

size_t ScriptFile::end() const { return group->end(); }

llvm::Value* ScriptFile::codegen(CodegenVisitor* v) const {
  return v->codegenScriptFile(*this);
}

}// namespace crane
