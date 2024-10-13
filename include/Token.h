#pragma once

#include <string>

namespace tenshi {
enum class TokenType {
  Word = 0,
  ChildList = 1, // Token that indicates that the following Values and Childs
                 // belong to the Node before the ":"
  QMarks = 2,    // " "
  Comma = 3 // Token that indicates that another Node or Value is following on
};

struct Token {
  TokenType m_Type;
  std::string m_Content;
};
} // namespace tenshi
