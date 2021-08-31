/***********************
 * @file: scanner.hpp
 * @author: shizuku
 * @date: 2021/7/11
 ***********************/
#pragma once

#include <memory>

#include "crane/error.hpp"
#include "crane/file.hpp"
#include "token.hpp"

namespace crane {

class Scanner {
public:
  Scanner() = delete;

  explicit Scanner(const std::shared_ptr<File>& f, ErrorHandler error);

public:
  Token scan();

  text_t scanIdent();

  std::tuple<TokenKind, text_t> scanNumber();

private:
  text_t scanRune();

  text_t scanString();

  text_t scanRawString();

  text_t scanComment();

  bool scanEscape(const rune_t& quote);

  bool findLineEnd();

private:
  TokenKind switch2(TokenKind tok0, TokenKind tok1);

  TokenKind switch3(TokenKind tok0, TokenKind tok1, rune_t ch2, TokenKind tok2);

  TokenKind switch4(TokenKind tok0, TokenKind tok1, rune_t ch2, TokenKind tok2, TokenKind tok3);

private:
  void next();

  rune_t peek();

  void digits(int base);

  void skipWhiteSpace();

private:
  static rune_t lower(rune_t c);

  static bool isDec(rune_t c);

  static bool isHex(rune_t c);

  static bool isLetter(rune_t c);

  static bool isDigit(rune_t c);

  static int digitVal(rune_t c);

  static text_t stripCR(const text_t& s, bool comment);

private:
  std::shared_ptr<File> file;
  std::shared_ptr<text_t> src;
  ErrorHandler error;

  rune_t ch;
  size_t offset;
  size_t readOffset;
  size_t lineOffset;
  bool insertSemi;
};

}// namespace crane
