// The Lexer is run first in the Deserialization Process
// It tokenizes the raw Input Data and returns the List of Tokens
#pragma once

#include "Types.h"
#include <vector>

namespace cytrus {
// Token Types
enum TokenType {
  Word,
  QMark,     // -> Quotation Mark(")
  NodeStart, // -> Symbol that follows after the Node Name(RootNode':')
  Separator  // -> Character that separates one Value from another(',';
};

struct Token {
  TokenType m_Type;
  std::string m_Content;
};

class Lexer {
public:
  // Splits up Data into List of Words and tokenizes them
  // Used by the Parser to parse the Data back into a Node Format
  // [return] std::vector<Token>: A vector that holds all Tokens sorted
  // [in] rawData: String of Data to tokenize
  static std::vector<Token> TokenizeData(const std::string &rawData);
};
} // namespace cytrus
