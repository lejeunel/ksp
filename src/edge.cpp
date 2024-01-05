#include "include/edge.h"
#include <algorithm>

Edge::Edge(NodePtr _source_node, NodePtr _target_node, scalar_t _length,
           bool a_occupied) {
  length = _length;
  orig_length = _length;
  source_node = _source_node;
  target_node = _target_node;
  occupied = a_occupied;
}

Edge::Edge(EdgePtr const &e) {
  length = e->length;
  source_node = e->source_node;
  target_node = e->target_node;
  occupied = e->occupied;
}

void Edge::invert() { length = -length; }
