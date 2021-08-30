/***********************
 * @file: field_list.hpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#pragma once

#include "expr.hpp"
#include "ident.hpp"

namespace crane {

struct Field : Expr {
  std::shared_ptr<Ident> name;
  std::shared_ptr<Expr> type;

  Field(std::shared_ptr<Ident> name, std::shared_ptr<Expr> type);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

struct FieldList : Expr {
  size_t opening;
  std::vector<std::shared_ptr<Field>> list;
  size_t closing;

  FieldList(size_t opening, std::vector<std::shared_ptr<Field>> list, size_t closing);

  [[nodiscard]] size_t beg() const override;
  [[nodiscard]] size_t end() const override;
};

}// namespace crane
