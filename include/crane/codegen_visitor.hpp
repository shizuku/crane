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

class BadExpr;
class Ident;
class BasicLit;

class UnaryExpr;
class BinaryExpr;
class ParenExpr;

class CallExpr;
class ReturnExpr;

class BlockExpr;
class ExprGroup;
class ExprList;
class FieldList;

struct CodegenVisitor {
  virtual llvm::Value* codegenBadExpr(const std::shared_ptr<BadExpr>& p) = 0;
  virtual llvm::Value* codegenIdent(const std::shared_ptr<Ident>& p) = 0;
  virtual llvm::Value* codegenBasicLit(const std::shared_ptr<BasicLit>& p) = 0;

  virtual llvm::Value* codegenBinaryExpr(const std::shared_ptr<BinaryExpr>& p) = 0;
  virtual llvm::Value* codegenParenExpr(const std::shared_ptr<ParenExpr>& p) = 0;
  virtual llvm::Value* codegenUnaryExpr(const std::shared_ptr<UnaryExpr>& p) = 0;

  virtual llvm::Value* codegenCallExpr(const std::shared_ptr<CallExpr>& p) = 0;
  virtual llvm::Value* codegenReturnExpr(const std::shared_ptr<ReturnExpr>& p) = 0;

  virtual llvm::Value* codegenBlockExpr(const std::shared_ptr<BlockExpr>& p) = 0;
  virtual llvm::Value* codegenExprGroup(const std::shared_ptr<ExprGroup>& p) = 0;
  virtual llvm::Value* codegenExprList(const std::shared_ptr<ExprList>& p) = 0;
  virtual llvm::Value* codegenFieldList(const std::shared_ptr<FieldList>& p) = 0;
};

}// namespace crane
