#include "OTree.h"

#include <iostream>

namespace cytrus {
// <== LEAF
Leaf *Leaf::GetPreviousNeighbour() {
  if (!m_Parent) {
    std::cout << "[Cytrus O-Tree] Leaf has no Parent" << std::endl;
    return nullptr;
  }

  i32 _indexOfThisLeaf = -1;
  for (i32 i = 0; i < m_Parent->m_Children.size(); i++) {
    if (this == m_Parent->m_Children[i]) {
      _indexOfThisLeaf = i;
      break;
    }
  }

  if (_indexOfThisLeaf <= 0)
    return nullptr;

  return m_Parent->m_Children[_indexOfThisLeaf - 1];
}

Leaf *Leaf::GetNextNeighbour() {
  if (!m_Parent) {
    std::cout << "[Cytrus O-Tree] Leaf has no Parent" << std::endl;
    return nullptr;
  }

  i32 _indexOfThisLeaf = -1;
  for (i32 i = 0; i < m_Parent->m_Children.size(); i++) {
    if (this == m_Parent->m_Children[i]) {
      _indexOfThisLeaf = i;
      break;
    }
  }

  if (_indexOfThisLeaf >= m_Parent->m_Children.size())
    return nullptr;

  return m_Parent->m_Children[_indexOfThisLeaf + 1];
}
} // namespace cytrus
