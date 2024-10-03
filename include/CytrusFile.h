#include "Node.h"
#include "Types.h"

#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace cytrus {
class CytrusFile {
public:
  explicit CytrusFile(const std::string &filePath);
  ~CytrusFile();

  // Recursevily Serializes the Node and its Children into the File while
  // keeping the Hierachy
  // [in] node: The Root Node to traverse down
  void SerializeNode(const Node &node);

  // Deserializes the given File and returns a Vector of Nodes
  // [return] std::vector<Node*>: Vector of Node Pointers
  std::vector<Node *> DeserializeFile();

private:
  bool OpenFile();
  void CloseFile();
  void Indent(u32 indentationLevel);

private:
  std::string m_FilePath;
  std::fstream m_FileStream;
};
} // namespace cytrus
