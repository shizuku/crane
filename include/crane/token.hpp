/***********************
 * @file: token.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace crane {

using size_t = unsigned long;
using text_t = std::string;
using rune_t = char;

enum TokenKind {
  tok_illegal,
  tok_comment,
  tok_eof,

  literal_beg,

  tok_ident,
  tok_int,
  tok_float,
  tok_rune,
  tok_string,

  literal_end,

  operator_beg,

  tok_add,// +
  tok_sub,// -
  tok_mul,// *
  tok_quo,// /
  tok_rem,// %

  tok_and,    // &
  tok_or,     // |
  tok_xor,    // ^
  tok_shl,    // <<
  tok_shr,    // >>
  tok_not,    // ~
  tok_and_not,// &^

  tok_assign,// =

  tok_add_assign,// +=
  tok_sub_assign,// -=
  tok_mul_assign,// *=
  tok_quo_assign,// /=
  tok_rem_assign,// %=

  tok_and_assign,    // &=
  tok_or_assign,     // |=
  tok_xor_assign,    // ^=
  tok_shl_assign,    // <<=
  tok_shr_assign,    // >>=
  tok_and_not_assign,// &^=

  tok_eql,// ==
  tok_neq,// !=
  tok_lss,// <
  tok_gtr,// >
  tok_leq,// <=
  tok_geq,// >=

  tok_inc,// ++
  tok_dec,// --

  tok_lnot,// !
  tok_lor, // ||
  tok_land,// &&

  tok_lor_assign, // ||=
  tok_land_assign,// &&=

  tok_lparen,// (
  tok_rparen,// )
  tok_lbrack,// [
  tok_rbrack,// ]
  tok_lbrace,// {
  tok_rbrace,// }

  tok_semicolon,  // ;
  tok_colon,      // :
  tok_comma,      // ,
  tok_period,     // .
  tok_elvis,      // ?:
  tok_null_period,// ?.
  tok_nullable,   // ?
  tok_notnull,    // !!
  tok_arrow,      // ->
  tok_util,       // ..
  tok_ellipsis,   // ...
  tok_ait,        // @

  operator_end,

  keyword_beg,

  tok_if,
  tok_else,
  tok_for,
  tok_while,
  tok_do,
  tok_break,
  tok_continue,
  tok_goto,
  tok_return,

  tok_var,
  tok_val,
  tok_fun,
  tok_enum,
  tok_class,
  tok_object,
  tok_trait,
  tok_interface,
  tok_annotation,

  tok_this,
  tok_null,
  tok_import,

  keyword_end,
};

constexpr static std::array<std::pair<TokenKind, std::string_view>, 100> tokenKinds{{
    {tok_illegal, "illegal"},
    {tok_comment, "comment"},
    {tok_eof, "eof"},

    {tok_ident, "ident"},
    {tok_int, "int"},
    {tok_float, "float"},
    {tok_rune, "rune"},
    {tok_string, "string"},

    {tok_add, "+"},
    {tok_sub, "-"},
    {tok_mul, "*"},
    {tok_quo, "/"},
    {tok_rem, "%"},

    {tok_and, "&"},
    {tok_or, "|"},
    {tok_xor, "^"},
    {tok_shl, "<<"},
    {tok_shr, ">>"},
    {tok_not, "~"},
    {tok_and_not, "&^"},

    {tok_assign, "="},

    {tok_add_assign, "+="},
    {tok_sub_assign, "-="},
    {tok_mul_assign, "*="},
    {tok_quo_assign, "/="},
    {tok_rem_assign, "%="},

    {tok_and_assign, "&="},
    {tok_or_assign, "|="},
    {tok_xor_assign, "^="},
    {tok_shl_assign, "<<="},
    {tok_shr_assign, ">>="},
    {tok_and_not_assign, "&^="},

    {tok_eql, "=="},
    {tok_neq, "!="},
    {tok_lss, "<"},
    {tok_gtr, ">"},
    {tok_leq, "<="},
    {tok_geq, ">="},

    {tok_inc, "++"},
    {tok_dec, "--"},

    {tok_lor, "||"},
    {tok_land, "&&"},
    {tok_lnot, "!"},

    {tok_lor_assign, "||="},
    {tok_land_assign, "&&="},

    {tok_lparen, "("},
    {tok_rparen, ")"},
    {tok_lbrack, "["},
    {tok_rbrack, "]"},
    {tok_lbrace, "{"},
    {tok_rbrace, "}"},

    {tok_semicolon, ";"},
    {tok_colon, ":"},
    {tok_comma, ","},
    {tok_period, "."},
    {tok_elvis, "?:"},
    {tok_nullable, "?"},
    {tok_null_period, "?."},
    {tok_notnull, "!!"},
    {tok_arrow, "->"},
    {tok_util, ".."},
    {tok_ellipsis, "..."},
    {tok_ait, "@"},

    {tok_if, "if"},
    {tok_else, "else"},
    {tok_for, "for"},
    {tok_while, "while"},
    {tok_do, "do"},
    {tok_break, "break"},
    {tok_continue, "continue"},
    {tok_goto, "goto"},
    {tok_return, "return"},

    {tok_var, "var"},
    {tok_val, "val"},
    {tok_fun, "fun"},
    {tok_class, "class"},
    {tok_object, "object"},
    {tok_trait, "trait"},
    {tok_interface, "interface"},
    {tok_enum, "enum"},
    {tok_annotation, "annotation"},

    {tok_this, "this"},
    {tok_null, "null"},
    {tok_import, "import"},
}};

constexpr static std::array<std::pair<TokenKind, std::string_view>, 21> keywords{{
    {tok_if, "if"},
    {tok_else, "else"},
    {tok_for, "for"},
    {tok_while, "while"},
    {tok_do, "do"},
    {tok_break, "break"},
    {tok_continue, "continue"},
    {tok_goto, "goto"},
    {tok_return, "return"},

    {tok_var, "var"},
    {tok_val, "val"},
    {tok_fun, "fun"},
    {tok_class, "class"},
    {tok_object, "object"},
    {tok_trait, "trait"},
    {tok_interface, "interface"},
    {tok_enum, "enum"},
    {tok_annotation, "annotation"},

    {tok_this, "this"},
    {tok_null, "null"},
    {tok_import, "import"},
}};

constexpr inline std::string_view to_string(const TokenKind& k) {
  for (auto& i : tokenKinds) {
    if (k == i.first) {
      return i.second;
    }
  }
  return "illegal";
}

constexpr inline TokenKind lookup(const std::string& ident) {
  for (auto& i : keywords) {
    if (i.second == ident) {
      return i.first;
    }
  }
  return tok_ident;
}

struct Token {
  TokenKind kind;
  size_t pos;
  text_t lit;

  Token();

  Token(TokenKind kind, size_t pos, text_t lit);

  [[nodiscard]] bool isLiteral() const;
  [[nodiscard]] bool isOperator() const;
  [[nodiscard]] bool isKeyword() const;

  [[nodiscard]] std::string toString() const;
};

std::ostream& operator<<(std::ostream& o, const Token& t);

const int lowestPrec = 0;
const int unaryPrec = 6;
const int highestPrec = 7;

int tokPrec(TokenKind k);

}// namespace crane
