// Ordered-Tree
#include "Types.h"

#include <vector>

namespace cytrus {
template <classname T> class Leaf {
  Leaf<T> *GetPreviousNeighbour();
  Leaf<T> *GetNextNeighbour();

  Leaf *m_Parent = nullptr;
  std::vector<Leaf *> m_Children;
};

class OTree {
public:
  OTree();
  ~OTree();

void

    public :
    // If you delete this manually fuck you
    Leaf *m_RootLeaf = nullptr;

private:
  // Count of all Leafs and their Children
  u32 m_TotalLeafs = 0;
};
} // namespace cytrus
