#include "Cytrus.h"

#include <iostream>

using namespace tenshi;

int main(int argc, char **argv) {
  CytrusFile _file("Data.cyt");
  Node _node("Root");
  _node.SetString("Root Value 1");
  _node.SetString("Root Value 2");

  _node["Child1"].SetString("Child1 Value 1");
  _node["Child1"].SetString("Child1 Value 2");
  _node["Child1"]["Test"]["TestChild"].SetString("Moin");

  Node _otherRootNode("Root2");
  _otherRootNode.SetString("Moin 2");
  _otherRootNode["AnotherChild"].SetString("Moin was geht");

  _file.SerializeNode(_node);
  _file.SerializeNode(_otherRootNode);

  std::vector<Node *> _deserializedNodes = _file.DeserializeFile();
  for (i32 i = 0; i < _deserializedNodes.size(); i++) {
    LOG("Deserialized Node " << i << ": " << _deserializedNodes[i]->m_Name);
  }

  return 0;
}
