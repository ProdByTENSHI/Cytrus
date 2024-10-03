#include "Lexer.h"

#include <iostream>

namespace cytrus {
std::vector<Token> Lexer::TokenizeData(const std::string &rawData) {
  std::vector<Token> _tokens;
  std::string _word;

  bool _isWord = false;
  for (char c : rawData) {
    if (c == ' ') {
      if (!_word.empty()) {
        Token _t;
        _t.m_Type = TokenType::Word;
        _t.m_Content = _word;
        _tokens.push_back(_t);
        _word.clear();
      }
      continue;
    }

    Token _t;

    switch (c) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':

    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      _isWord = true;
      _word += c;
      break;

    case '"':
      _isWord = false;
      _t.m_Type = TokenType::QMark;
      _t.m_Content = '"';
      _tokens.push_back(_t);
      break;

    case ':':
      _isWord = false;
      _t.m_Type = TokenType::NodeStart;
      _t.m_Content = ':';
      _tokens.push_back(_t);
      break;

    case ',':
      _isWord = false;
      _t.m_Type = TokenType::Separator;
      _t.m_Content = ',';
      _tokens.push_back(_t);
      break;
    }

    if (_isWord)
      continue;

    _t.m_Type = TokenType::Word;
    _t.m_Content = _word;
    _tokens.push_back(_t);
    _word.clear();
  }

  for (i32 i = 0; i < _tokens.size(); i++) {
    std::cout << "[Lexer] Token " << i << ": " << _tokens[i].m_Content
              << std::endl;
  }

  return _tokens;
}
} // namespace cytrus
