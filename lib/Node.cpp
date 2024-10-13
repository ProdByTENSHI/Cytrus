#include "Node.h"

#include <iostream>

namespace tenshi {
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

Node &Node::operator[](const std::string &key) { return AddChild(key); }

Node &Node::AddChild(const std::string &key) {
  if (m_ChildNodes.find(key) == m_ChildNodes.end()) {
    m_ChildNodes[key] = new Node(key);
    return *m_ChildNodes[key];
  }

  return *m_ChildNodes[key];
}

void Node::AddChild(Node &node) { m_ChildNodes[node.m_Name] = &node; }

void Node::Print() {
  std::cout << "Data of " << m_Name << std::endl;

  for (i32 i = 0; i < m_Content.size(); i++) {
    std::cout << "\t" << m_Content[i] << std::endl;
  }

  for (auto &node : m_ChildNodes) {
    node.second->Print();
  }
}
} // namespace tenshi
