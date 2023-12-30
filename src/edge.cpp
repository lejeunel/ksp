#include "include/edge.h"
#include <algorithm>

Edge::Edge(std::shared_ptr<Node> _start_node,
                std::shared_ptr<Node> _end_node, scalar_t _length) {
  length = _length;
  start_node = _start_node;
  end_node = _end_node;
}

void Edge::invert() {
  length = -length;
  positivized_length = -positivized_length;
}
