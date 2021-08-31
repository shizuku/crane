/***********************
 * @file: scanner.cpp
 * @author: shizuku
 * @date: 2021/7/12
 ***********************/
#include "crane/scanner.hpp"

#include <utility>

namespace crane {

Scanner::Scanner(const std::shared_ptr<File>& f, ErrorHandler error)
    : file{f}, src{f->content}, error{std::move(error)},
      ch{' '}, offset{0}, readOffset{0}, lineOffset{0}, insertSemi{false} {
  next();
}

Token Scanner::scan() {
  skipWhiteSpace();
  text_t lit;
  TokenKind kind = tok_illegal;
  auto pos = offset;
  auto istSemi = false;
  auto c = ch;
  if (isLetter(c)) {
    lit = scanIdent();
    if (lit.size() > 1) {
      kind = lookup(lit);
      switch (kind) {
        case tok_ident:
        case tok_break:
        case tok_continue:
        case tok_return:
          istSemi = true;
          break;
        default:
          break;
      }
    } else {
      kind = tok_ident;
      istSemi = true;
    }
  } else if (isDec(c) || (c == '.' && isDec(peek()))) {
    std::tie(kind, lit) = scanNumber();
    istSemi = true;
  } else {
    next();
    switch (c) {
      case -1:
        if (insertSemi) {
          insertSemi = false;
          return {tok_semicolon, pos, "\n"};
        }
        kind = tok_eof;
        break;
      case '\n':
        insertSemi = false;
        return {tok_semicolon, pos, "\n"};
      case '"':
        istSemi = true;
        lit = scanString();
        kind = tok_string;
        break;
      case '\'':
        istSemi = true;
        lit = scanRune();
        kind = tok_rune;
        break;
      case '`':
        istSemi = true;
        lit = scanRawString();
        kind = tok_string;
        break;
      case '+':
        kind = switch3(tok_add, tok_add_assign, '+', tok_inc);
        if (kind == tok_inc) {
          istSemi = true;
        }
        break;
      case '-':
        if (ch == '>') {
          next();
          kind = tok_arrow;
        } else {
          kind = switch3(tok_sub, tok_sub_assign, '-', tok_dec);
          if (kind == tok_dec) {
            istSemi = true;
          }
        }
        break;
      case '*':
        kind = switch2(tok_mul, tok_mul_assign);
        break;
      case '/':
        if (ch == '*' || ch == '/') {
          if (insertSemi && findLineEnd()) {
            ch = '/';
            offset = pos;
            readOffset = offset + 1;
            insertSemi = false;
            return {tok_semicolon, pos, "\n"};
          }
          auto comment = scanComment();
          kind = tok_comment;
          lit = comment;
        } else {
          kind = switch2(tok_quo, tok_quo_assign);
        }
        break;
      case '%':
        kind = switch2(tok_rem, tok_rem_assign);
        break;
      case '&':
        if (ch == '^') {
          next();
          if (ch == '=') {
            next();
            kind = tok_and_not_assign;
          } else {
            kind = tok_and_not;
          }
        } else {
          kind = switch4(tok_and, tok_and_assign, '&', tok_land, tok_land_assign);
        }
        break;
      case '|':
        kind = switch4(tok_or, tok_or_assign, '|', tok_lor, tok_lor_assign);
        break;
      case '^':
        kind = switch2(tok_xor, tok_xor_assign);
        break;
      case '<':
        kind = switch4(tok_lss, tok_leq, '<', tok_shl, tok_shl_assign);
        break;
      case '>':
        kind = switch4(tok_gtr, tok_geq, '>', tok_shr, tok_shr_assign);
        break;
      case '~':
        kind = tok_not;
        break;
      case '=':
        kind = switch2(tok_assign, tok_eql);
        break;
      case ';':
        kind = tok_semicolon;
        lit = ";";
        break;
      case ':':
        kind = tok_colon;
        break;
      case '.':
        if (ch == '.') {
          next();
          if (ch == '.') {
            next();
            kind = tok_ellipsis;
          } else {
            kind = tok_util;
          }
        } else {
          kind = tok_period;
        }
        break;
      case ',':
        kind = tok_comma;
        break;
      case '?':
        if (ch == '.') {
          next();
          kind = tok_null_period;
        } else if (ch == ':') {
          next();
          kind = tok_elvis;
        } else {
          kind = tok_nullable;
        }
        break;
      case '!':
        if (ch == '!') {
          next();
          kind = tok_notnull;
        } else {
          kind = switch2(tok_lnot, tok_neq);
        }
        break;
      case '(':
        kind = tok_lparen;
        break;
      case ')':
        kind = tok_rparen;
        istSemi = true;
        break;
      case '[':
        kind = tok_lbrack;
        break;
      case ']':
        kind = tok_rbrack;
        istSemi = true;
        break;
      case '{':
        kind = tok_lbrace;
        break;
      case '}':
        kind = tok_rbrace;
        istSemi = true;
        break;
      case '@':
        kind = tok_ait;
        break;
      default:
        istSemi = insertSemi;
        kind = tok_illegal;
        error(pos, "unexpected char");
        break;
    }
  }
  insertSemi = istSemi;
  return {kind, pos, lit};
}

text_t Scanner::scanIdent() {
  auto pos = offset;
  while (isLetter(ch) || isDigit(ch) || ch == '_') {
    next();
  }
  return src->substr(pos, offset - pos);
}

std::tuple<TokenKind, text_t> Scanner::scanNumber() {
  auto pos = offset;
  int base = 10;
  auto tok = tok_illegal;
  if (ch != '.') {
    tok = tok_int;
    if (ch == '0') {
      next();
      switch (lower(ch)) {
        case 'x':
          base = 16;
          next();
          break;
        case 'o':
          base = 8;
          next();
          break;
        case 'b':
          base = 2;
          next();
          break;
        default:
          base = 8;
          break;
      }
    }
    digits(base);
  }
  if (ch == '.') {
    next();
    tok = tok_float;
    digits(base);
  }
  auto lit = src->substr(pos, offset - pos);
  return std::make_tuple(tok, lit);
}

text_t Scanner::scanRune() {
  auto pos = offset - 1;
  auto valid = true;
  auto n = 0;
  for (;;) {
    auto c = ch;
    if (c == '\n' || c < 0) {
      if (valid) {
        error(pos, "rune literal not terminated");
        valid = false;
      }
      break;
    }
    next();
    if (c == '\'') {
      break;
    }
    n++;
    if (c == '\\') {
      if (!scanEscape('\'')) {
        valid = false;
      }
    }
  }
  if (valid && n != 1) {
    error(pos, "illegal rune literal");
  }
  return src->substr(pos, offset - pos);
}

text_t Scanner::scanString() {
  auto pos = offset - 1;
  for (;;) {
    auto c = ch;
    if (c == '\n' || c < 0) {
      error(pos, "string literal not terminated");
      break;
    }
    next();
    if (c == '"') {
      break;
    }
    if (c == '\\') {
      scanEscape('"');
    }
  }
  return src->substr(pos, offset - pos);
}

text_t Scanner::scanRawString() {
  auto pos = offset - 1;
  auto hasCR = false;
  for (;;) {
    auto c = ch;
    if (c < 0) {
      error(pos, "raw string literal not terminated");
      break;
    }
    next();
    if (c == '`') {
      break;
    }
    if (c == '\r') {
      hasCR = true;
    }
  }
  auto lit = src->substr(pos, offset - pos);
  if (hasCR) {
    lit = stripCR(lit, false);
  }
  return lit;
}

text_t Scanner::scanComment() {
  auto pos = offset - 1;
  int nex = -1;
  int numCR = 0;
  if (ch == '/') {
    //
    next();
    while (ch != '\n' && ch >= 0) {
      if (ch == '\r') {
        numCR++;
      }
      next();
    }
    nex = int(offset);
    if (ch == '\n') {
      nex++;
    }
    goto exit;
  }

  /**/
  next();
  while (ch >= 0) {
    auto c = ch;
    if (c == '\r') {
      numCR++;
    }
    next();
    if (c == '*' && ch == '/') {
      next();
      nex = int(offset);
      goto exit;
    }
  }
  error(pos, "comment not terminated");
exit:
  auto lit = src->substr(pos, offset - pos);
  if (numCR > 0 && lit.size() > 2 && lit[1] == '/' && lit[lit.size() - 1] == '\r') {
    lit = lit.substr(0, lit.size() - 1);
    numCR--;
  }
  if (numCR > 0) {
    lit = stripCR(lit, lit[1] == '*');
  }
  return lit;
}

bool Scanner::scanEscape(const rune_t& quote) {
  auto pos = offset;
  int n = 0;
  unsigned base = 0, max = 0;
  if (ch == quote) {
    next();
    return true;
  }
  switch (ch) {
    case 'a':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
    case 'v':
    case '\\':
      next();
      return true;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
      n = 3;
      base = 8;
      max = 255;
      break;
    case 'x':
      next();
      n = 2;
      base = 16;
      max = 255;
      break;
    case 'u':
      next();
      n = 4;
      base = 16;
      max = 1114111;
      break;
    case 'U':
      next();
      n = 8;
      base = 16;
      max = 1114111;
      break;
    default:
      std::string msg = "unknown escape sequence";
      if (ch < 0) {
        msg = "escape sequence not terminated";
      }
      error(pos, msg);
      return false;
  }
  unsigned x = 0;
  while (n > 0) {
    unsigned d = digitVal(ch);
    if (d >= base) {
      std::string msg = "illegal character";
      if (ch < 0) {
        msg = "escape sequence not terminated";
      }
      error(offset, msg);
      return false;
    }
    x = x * base + d;
    next();
    n--;
  }
  if (x > max || 0xd800 <= x && x < 0xe000) {
    error(pos, "escape sequence is invalid Unicode code point");
    return false;
  }
  return true;
}

bool Scanner::findLineEnd() {
  auto pos = offset - 1;
  auto reset = [&]() {
    ch = '/';
    offset = pos;
    readOffset = pos + 1;
    next();
  };
  while (ch == '/' || ch == '*') {
    if (ch == '/') {
      reset();
      return true;
    }
    next();
    while (ch >= 0) {
      auto c = ch;
      if (c == '\n') {
        reset();
        return true;
      }
      next();
      if (c == '*' && ch == '\n') {
        next();
        break;
      }
    }
    skipWhiteSpace();
    if (ch < 0 || ch == '\n') {
      reset();
      return true;
    }
    if (ch != '/') {
      reset();
      return false;
    }
    next();
  }
  reset();
  return false;
}

TokenKind Scanner::switch2(TokenKind tok0, TokenKind tok1) {
  if (ch == '=') {
    next();
    return tok1;
  }
  return tok0;
}

TokenKind Scanner::switch3(TokenKind tok0, TokenKind tok1, rune_t ch2, TokenKind tok2) {
  if (ch == '=') {
    next();
    return tok1;
  }
  if (ch == ch2) {
    next();
    return tok2;
  }
  return tok0;
}

TokenKind Scanner::switch4(TokenKind tok0, TokenKind tok1, rune_t ch2, TokenKind tok2, TokenKind tok3) {
  if (ch == '=') {
    next();
    return tok1;
  }
  if (ch == ch2) {
    next();
    if (ch == '=') {
      next();
      return tok3;
    }
    return tok2;
  }
  return tok0;
}

void Scanner::next() {
  if (readOffset < src->size()) {
    offset = readOffset;
    if (ch == '\n') {
      lineOffset = offset;
      file->addLine(offset);
    }
    ch = src->at(readOffset);
    readOffset++;
  } else {
    offset = src->size();
    if (ch == '\n') {
      lineOffset = offset;
      file->addLine(offset);
    }
    ch = -1;
  }
}

rune_t Scanner::peek() {
  if (readOffset < src->size()) {
    return src->at(readOffset);
  }
  return 0;
}

void Scanner::digits(int base) {
  if (base <= 10) {
    while (isDec(ch) || ch == '_') {
      next();
    }
  } else {
    while (isHex(ch) || ch == '_') {
      next();
    }
  }
}

void Scanner::skipWhiteSpace() {
  while (ch == ' ' || ch == '\t' || (ch == '\n' && !insertSemi) || ch == '\r') {
    next();
  }
}

rune_t Scanner::lower(rune_t c) { return rune_t(('a' - 'A') | c); }

bool Scanner::isDec(rune_t c) { return c >= '0' && c <= '9'; }

bool Scanner::isHex(rune_t c) {
  return (c >= '0' && c <= '9') || (lower(c) >= 'a' && lower(c) <= 'f');
}

bool Scanner::isLetter(rune_t c) {
  return lower(c) >= 'a' && lower(c) <= 'z';
}

bool Scanner::isDigit(rune_t c) { return isDec(c); }

text_t Scanner::stripCR(const text_t& b, bool comment) {
  text_t c{};
  c.reserve(b.size());
  int i = 0;
  for (int j = 0; j < b.size(); j++) {
    if (b[j] != '\r' || comment && i > text_t("/*").size() && c[i - 1] == '*' && j + 1 < b.size() && b[j + 1] == '/') {
      c[i] = b[j];
      i++;
    }
  }
  c.shrink_to_fit();
  return c;
}

int Scanner::digitVal(rune_t ch) {
  if ('0' <= ch && ch <= '9') {
    return ch - '0';
  }
  if ('a' <= lower(ch) && lower(ch) <= 'f') {
    return lower(ch) - 'a' + 10;
  }
  return 16;
}

}// namespace crane
