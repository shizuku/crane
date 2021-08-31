/***********************
 * @file: code_generator.cpp
 * @author: shizuku
 * @date: 2021/8/30
 ***********************/
#include "crane/code_generator.hpp"

namespace crane {

CodeGenerator::CodeGenerator(const std::string& moduleId, ErrorHandler error)
    : error{std::move(error)} {
  context = std::make_unique<llvm::LLVMContext>();
  module = std::make_unique<llvm::Module>(moduleId, *context);
  builder = std::make_unique<llvm::IRBuilder<>>(*context);
}

llvm::Value* CodeGenerator::codegenScriptFile(const ScriptFile& p) {
  return p.group->codegen(this);
}

llvm::Value* CodeGenerator::codegenBlockExpr(const BlockExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenExprGroup(const ExprGroup& p) {
  llvm::Value* r = nullptr;
  for (auto& i : p.list) {
    r = i->codegen(this);
  }
  return r;
}

llvm::Value* CodeGenerator::codegenExprList(const ExprList& p) {
  llvm::Value* r = nullptr;
  for (auto& i : p.list) {
    r = i->codegen(this);
  }
  return r;
}

llvm::Value* CodeGenerator::codegenFieldList(const FieldList& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenCallExpr(const CallExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenReturnExpr(const ReturnExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenBinaryExpr(const BinaryExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenUnaryExpr(const UnaryExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenParenExpr(const ParenExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenBadExpr(const BadExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenIdent(const Ident& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenBasicLit(const BasicLit& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenFunDeclExpr(const FunDeclExpr& p) {
  return nullptr;
}

llvm::Value* CodeGenerator::codegenVarDeclExpr(const VarDeclExpr& x) {
  llvm::Value* value = nullptr;
  if (x.value) {
    value = x.value->codegen(this);
  }
  llvm::Type* type = nullptr;
  if (x.type) {
    type = getType(x.type);
  } else if (value) {
    type = value->getType();
  } else {
    error(x.name->end(), "variable must have type or be inited");
  }
  auto a = builder->CreateAlloca(type, nullptr, x.name->name);
  setVariable(x.name->name, a);
  if (value) {
    if (type->getTypeID() != value->getType()->getTypeID()) {
      error(x.value->beg(), "incorrect type");
    }
    builder->CreateStore(value, a, false);
  }
  return a;
  return nullptr;
}

llvm::Value* CodeGenerator::codegenValDeclExpr(const ValDeclExpr& p) {
  return nullptr;
}

}// namespace crane
