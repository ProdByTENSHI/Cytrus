// The Lexer is run first in the Deserialization Process
// It tokenizes the raw Input Data and returns the List of Tokens
#pragma once

#include "Types.h"
#include <vector>

namespace cytrus {
// Token Types
enum Token {
  Node,
  QMark,     // -> Quotation Mark(")
  NodeStart, // -> Symbol that follows after the Node Name(RootNode':')
  Separator  // -> Character that separates one Value from another(',')
};

class Lexer {
public:
  static std::vector<Token> TokenizeData(const std::string &rawData);
};
} // namespace cytrus
