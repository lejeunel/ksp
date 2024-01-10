#include "include/edge.h"

Edge::Edge(int const &_id, Node *_source_node, Node *_target_node,
           scalar_t _length) {
  id = _id;
  length = _length;
  orig_length = _length;
  source_node = _source_node;
  target_node = _target_node;
}

Edge::Edge(Edge *e) {
  length = e->length;
  source_node = e->source_node;
  target_node = e->target_node;
  occupied = e->occupied;
  interlaced = e->interlaced;
}

std::ostream &operator<<(std::ostream &os, const Edge &e) {
  os << e.source_node->get_id() << " -> " << e.target_node->get_id()
     << " id: " << e.id;
  return os;
}
