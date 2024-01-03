#include "include/edge.h"
#include <algorithm>

Edge::Edge(std::shared_ptr<Node> _source_node, std::shared_ptr<Node> _target_node,
           scalar_t _length) {
  length = _length;
  source_node = _source_node;
  target_node = _target_node;
}

void Edge::invert() {
  length = -length;
  positivized_length = -positivized_length;
}

std::shared_ptr<Node> Edge::get_source_node() { return source_node; }
std::shared_ptr<Node> Edge::get_target_node() { return target_node; }
