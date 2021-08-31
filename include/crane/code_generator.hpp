/***********************
 * @file: code_generator.hpp
 * @author: shizuku
 * @date: 2021/8/30
 ***********************/
#pragma once

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <utility>

#include "crane/ast/bad_expr.hpp"
#include "crane/ast/basic_lit.hpp"
#include "crane/ast/binary_expr.hpp"
#include "crane/ast/block_expr.hpp"
#include "crane/ast/call_expr.hpp"
#include "crane/ast/decl/fun_decl_expr.hpp"
#include "crane/ast/decl/val_decl_expr.hpp"
#include "crane/ast/decl/var_decl_expr.hpp"
#include "crane/ast/expr_group.hpp"
#include "crane/ast/expr_list.hpp"
#include "crane/ast/field_list.hpp"
#include "crane/ast/ident.hpp"
#include "crane/ast/paren_expr.hpp"
#include "crane/ast/return_expr.hpp"
#include "crane/ast/script.hpp"
#include "crane/ast/unary_expr.hpp"
#include "crane/codegen_visitor.hpp"
#include "crane/error.hpp"

namespace crane {

struct CodeGenerator : CodegenVisitor {
  std::shared_ptr<llvm::LLVMContext> context;
  std::shared_ptr<llvm::Module> module;
  std::shared_ptr<llvm::IRBuilder<>> builder;

  ErrorHandler error;

  CodeGenerator(const std::string& moduleId, ErrorHandler error);

  llvm::Value* codegenScriptFile(const ScriptFile& p) override;

  llvm::Value* codegenBlockExpr(const BlockExpr& p) override;
  llvm::Value* codegenExprGroup(const ExprGroup& p) override;
  llvm::Value* codegenExprList(const ExprList& p) override;
  llvm::Value* codegenFieldList(const FieldList& p) override;

  llvm::Value* codegenCallExpr(const CallExpr& p) override;
  llvm::Value* codegenReturnExpr(const ReturnExpr& p) override;

  llvm::Value* codegenBinaryExpr(const BinaryExpr& p) override;
  llvm::Value* codegenUnaryExpr(const UnaryExpr& p) override;
  llvm::Value* codegenParenExpr(const ParenExpr& p) override;

  llvm::Value* codegenBadExpr(const BadExpr& p) override;
  llvm::Value* codegenIdent(const Ident& p) override;
  llvm::Value* codegenBasicLit(const BasicLit& p) override;

  llvm::Value* codegenFunDeclExpr(const FunDeclExpr& p) override;
  llvm::Value* codegenVarDeclExpr(const VarDeclExpr& p) override;
  llvm::Value* codegenValDeclExpr(const ValDeclExpr& p) override;


  llvm::Type* typegenIdent(const Ident& x);
};

}// namespace crane
