#include "Types.h"

#include <fstream>
#include <map>
#include <string>
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

class CytrusFile {
public:
  explicit CytrusFile(const std::string &filePath);
  ~CytrusFile();

  // Recursevily Serializes the Node and its Children into the File while
  // keeping the Hierachy
  // [in] node: The Root Node to traverse down
  void SerializeNode(const Node &node);

private:
  void OpenFile();
  void CloseFile();
  void Indent(u32 indentationLevel);

private:
  std::string m_FilePath;
  std::fstream m_FileStream;
};
} // namespace cytrus
