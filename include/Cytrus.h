#include "Node.h"
#include "Token.h"
#include "Types.h"

#include <fstream>
#include <string>
#include <vector>

namespace tenshi {
class CytrusFile {
public:
  explicit CytrusFile(const std::string &filePath);
  ~CytrusFile();

  // Recursevily Serializes the Node and its Children into the File while
  // keeping the Hierachy
  // [in] node: The Root Node to traverse down
  void SerializeNode(const Node &node);

  // Splits the Raw Text Data into Tokens that get Parsed by the Parser
  std::vector<Token> Tokenize(const std::string &input);

  // Parses the Tokens and creates the Nodes and Values
  std::vector<Node *> Parse(const std::vector<Token> &tokens);

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
} // namespace tenshi
