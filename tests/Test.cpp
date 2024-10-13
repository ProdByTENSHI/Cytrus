#include "Cytrus.h"

int main(int argc, char **argv) {
  tenshi::CytrusFile _file("Data.cyt");
  tenshi::Node _node("Root");
  _node.SetString("Root Value 1");
  _node.SetString("Root Value 2");

  _node["Child1"].SetString("Child1 Value 1");
  _node["Child1"].SetString("Child1 Value 2");
  _node["Child1"]["Test"]["TestChild"].SetString("Moin");

  tenshi::Node _otherRootNode("Root2");
  _otherRootNode.SetString("Moin 2");
  _otherRootNode["AnotherChild"].SetString("Moin was geht");

  _file.SerializeNode(_node);
  _file.SerializeNode(_otherRootNode);

  std::vector<tenshi::Node *> _deserializedNodes = _file.DeserializeFile();

  return 0;
}
