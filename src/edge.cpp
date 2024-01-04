#include "include/edge.h"
#include <algorithm>

Edge::Edge(NodePtr _source_node, NodePtr _target_node, scalar_t _length) {
  length = _length;
  source_node = _source_node;
  target_node = _target_node;
}

void Edge::invert() {
  length = -length;
  positivized_length = -positivized_length;
}
