#include "../node.hpp"

int main(void) {
  NodeList nl;
  Nnode *node;
  node = Nnode::MakeNode(6, "avbd");
  nl.add(node);
  nl.Debug();
  return 0;
}