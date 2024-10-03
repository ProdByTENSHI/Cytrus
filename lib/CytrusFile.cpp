#include "CytrusFile.h"

#include <iostream>

namespace cytrus {
// <=== NODE ===>
Node::Node(const std::string &name) : m_Name(name) {}

u32 Node::SetString(const std::string &value) {
  for (i32 i = 0; i < m_Content.size(); i++) {
    if (m_Content[i] != value)
      continue;

    m_Content[i] = value;
    return i;
  }

  m_Content.push_back(value);
  return m_Content.size() - 1;
}

std::string Node::GetString(u32 index) {
  if (m_Content.size() - 1 < index) {
    std::cout << "[Cytrus] Error: Could not get String at index " << index
              << std::endl;
    return "";
  }

  return m_Content[index];
}

Node &Node::operator[](const std::string &key) {
  if (m_ChildNodes.find(key) == m_ChildNodes.end()) {
    m_ChildNodes[key] = new Node(key);
    return *m_ChildNodes[key];
  }

  return *m_ChildNodes[key];
}

// <=== CYTRUS FILE ===>
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
  std::cout << "[Cytrus] Indentation Level for Node " << node.m_Name << ": "
            << indentationLevel << std::endl;

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

void CytrusFile::OpenFile() {
  if (m_FileStream.is_open()) {
    std::cout << "[Cytrus] File is already opened" << std::endl;
    return;
  }

  m_FileStream.open(m_FilePath, std::ios::out | std::ios::app);
  if (!m_FileStream.is_open()) {
    std::cout << "[Cytrus] Error: Could not open File " << m_FilePath
              << std::endl;
    return;
  }
}

void CytrusFile::CloseFile() { m_FileStream.close(); }

void CytrusFile::Indent(u32 indentationLevel) {
  for (u32 i = 0; i < indentationLevel; i++) {
    m_FileStream << " ";
  }

  m_FileStream.flush();
}

} // namespace cytrus
