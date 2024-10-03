#pragma once

#include "Types.h"

#include <map>
#include <vector>

namespace cytrus {
inline const u32 INDENTATION_PER_NODE_LEVEL = 2;

class Node {
public:
  explicit Node(const std::string &name);

  // Either Overwrites or Pushes Back the given String into the Nodes Value
  // List [returns] u32: The Index where the String was placed [in] value:
  // Value to write
  u32 SetString(const std::string &value);

  // Returns the String at the given Index
  // [in] index: The Index where the String is located in the Vector
  std::string GetString(u32 index);

  // Subscript Operator Overload to create Child Nodes easily
  Node &operator[](const std::string &key);

public:
  // Holds all Children Nodes by their Name
  std::map<std::string, Node *> m_ChildNodes;

  const std::string m_Name;

  // Values of this Node
  std::vector<std::string> m_Content;
};

} // namespace cytrus
