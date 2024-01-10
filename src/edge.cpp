#include "include/edge.h"

Edge::Edge(int const &_id, Node *a_tail, Node *a_head, scalar_t _length)
    : id(_id), length(_length), _tail(a_tail), _head(a_head),
      orig_length(_length) {}

std::ostream &operator<<(std::ostream &os, const Edge &e) {
  os << e._tail->get_id() << " -> " << e._head->get_id() << " id: " << e.id;
  return os;
}
