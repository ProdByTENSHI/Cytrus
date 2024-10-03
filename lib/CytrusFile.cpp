#include "CytrusFile.h"

#include "Lexer.h"

#include <iostream>
#include <sstream>

namespace cytrus {
CytrusFile::CytrusFile(const std::string &filePath) : m_FilePath(filePath) {}

CytrusFile::~CytrusFile() {}

/* FILE FORMAT:
* Node:
        "Content",
        "Content2",
        "Content3",

        Child-Node:
                …
                …
                …
*/
void CytrusFile::SerializeNode(const Node &node) {
  static u32 indentationLevel = 0;

  OpenFile();
  Indent(indentationLevel);
  m_FileStream << node.m_Name << ":\n";

  indentationLevel += INDENTATION_PER_NODE_LEVEL;
  for (u32 i = 0; i < node.m_Content.size(); i++) {
    Indent(indentationLevel);

    auto &_value = node.m_Content[i];
    m_FileStream << '\u0022' << _value << '\u0022';
    if (node.m_ChildNodes.size() > 0 ||
        (i < node.m_Content.size() - 1 && node.m_Content.size() != 0)) {
      m_FileStream << ",";
    }

    m_FileStream << std::endl;
  }

  if (node.m_ChildNodes.size() <= 0) {
    indentationLevel = 0;
    m_FileStream.close();
  }

  for (auto &child : node.m_ChildNodes) {
    indentationLevel += INDENTATION_PER_NODE_LEVEL;
    SerializeNode(*child.second);
  }
}

std::vector<Node *> CytrusFile::DeserializeFile() {
  std::vector<Node *> _data;

  if (!OpenFile())
    return _data;

  std::stringstream _buffer;
  _buffer << m_FileStream.rdbuf();

  Lexer::TokenizeData(_buffer.str());

  return _data;
}

bool CytrusFile::OpenFile() {
  if (m_FileStream.is_open()) {
    return true;
  }

  m_FileStream.open(m_FilePath, std::ios::in | std::ios::out | std::ios::app);
  if (!m_FileStream.is_open()) {
    std::cout << "[Cytrus] Error: Could not open File " << m_FilePath
              << std::endl;
    return false;
  }

  return true;
}

void CytrusFile::CloseFile() { m_FileStream.close(); }

void CytrusFile::Indent(u32 indentationLevel) {
  for (u32 i = 0; i < indentationLevel; i++) {
    m_FileStream << " ";
  }

  m_FileStream.flush();
}

} // namespace cytrus
