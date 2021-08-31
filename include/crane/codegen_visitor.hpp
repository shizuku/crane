/***********************
 * @file: codegen_visitor.hpp
 * @author: shizuku
 * @date: 2021/8/30
 ***********************/
#pragma once

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <memory>

namespace crane {

class ScriptFile;

class BlockExpr;
class ExprGroup;
class ExprList;
class FieldList;

class BadExpr;
class Ident;
class BasicLit;

class CallExpr;
class ReturnExpr;

class UnaryExpr;
class BinaryExpr;
class ParenExpr;

class FunDeclExpr;
class VarDeclExpr;
class ValDeclExpr;

struct CodegenVisitor {
  virtual llvm::Value* codegenScriptFile(const ScriptFile& p) = 0;

  virtual llvm::Value* codegenBlockExpr(const BlockExpr& p) = 0;
  virtual llvm::Value* codegenExprGroup(const ExprGroup& p) = 0;
  virtual llvm::Value* codegenExprList(const ExprList& p) = 0;
  virtual llvm::Value* codegenFieldList(const FieldList& p) = 0;

  virtual llvm::Value* codegenCallExpr(const CallExpr& p) = 0;
  virtual llvm::Value* codegenReturnExpr(const ReturnExpr& p) = 0;

  virtual llvm::Value* codegenBinaryExpr(const BinaryExpr& p) = 0;
  virtual llvm::Value* codegenParenExpr(const ParenExpr& p) = 0;
  virtual llvm::Value* codegenUnaryExpr(const UnaryExpr& p) = 0;

  virtual llvm::Value* codegenBadExpr(const BadExpr& p) = 0;
  virtual llvm::Value* codegenIdent(const Ident& p) = 0;
  virtual llvm::Value* codegenBasicLit(const BasicLit& p) = 0;

  virtual llvm::Value* codegenFunDeclExpr(const FunDeclExpr& p) = 0;
  virtual llvm::Value* codegenVarDeclExpr(const VarDeclExpr& p) = 0;
  virtual llvm::Value* codegenValDeclExpr(const ValDeclExpr& p) = 0;

  virtual llvm::Type* typegenScriptFile(const ScriptFile& p) = 0;

  virtual llvm::Type* typegenBlockExpr(const BlockExpr& p) = 0;
  virtual llvm::Type* typegenExprGroup(const ExprGroup& p) = 0;
  virtual llvm::Type* typegenExprList(const ExprList& p) = 0;
  virtual llvm::Type* typegenFieldList(const FieldList& p) = 0;

  virtual llvm::Type* typegenCallExpr(const CallExpr& p) = 0;
  virtual llvm::Type* typegenReturnExpr(const ReturnExpr& p) = 0;

  virtual llvm::Type* typegenBinaryExpr(const BinaryExpr& p) = 0;
  virtual llvm::Type* typegenParenExpr(const ParenExpr& p) = 0;
  virtual llvm::Type* typegenUnaryExpr(const UnaryExpr& p) = 0;

  virtual llvm::Type* typegenBadExpr(const BadExpr& p) = 0;
  virtual llvm::Type* typegenIdent(const Ident& p) = 0;
  virtual llvm::Type* typegenBasicLit(const BasicLit& p) = 0;

  virtual llvm::Type* typegenFunDeclExpr(const FunDeclExpr& p) = 0;
  virtual llvm::Type* typegenVarDeclExpr(const VarDeclExpr& p) = 0;
  virtual llvm::Type* typegenValDeclExpr(const ValDeclExpr& p) = 0;
};

}// namespace crane
