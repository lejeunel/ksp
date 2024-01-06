#include "include/edge.h"
#include "include/node.h"
#include <algorithm>

Edge::Edge(NodePtr _source_node, NodePtr _target_node, scalar_t _length) {
  length = _length;
  orig_length = _length;
  source_node = _source_node;
  target_node = _target_node;
}

Edge::Edge(EdgePtr const &e) {
  length = e->length;
  source_node = e->source_node;
  target_node = e->target_node;
  occupied = e->occupied;
  interlaced = e->interlaced;
}

EdgeList Edge::get_edges_at_head() { return target_node->out_edges; }
