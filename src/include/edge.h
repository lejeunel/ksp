#ifndef EDGE_H_
#define EDGE_H_
#include "common.h"
#include "node.h"
#include <memory>
#include <string>

class Edge {
public:
  Edge(int const &a_id, Node *a_tail, Node *a_head, scalar_t _length);
  Node *tail() { return _tail; }
  Node *head() { return _head; }
  bool is_occupied() { return occupied; }
  void set_occupied(const bool &val) { occupied = val; }
  bool is_interlaced() { return interlaced; }
  void set_interlaced(const bool &val) { interlaced = val; }
  bool is_used() { return used; }
  void set_used(const bool &val) { used = val; }
  void set_length(const int &l) { length = l; }
  void reset_length() { length = orig_length; }
  int get_length() const { return length; }
  int get_id() const { return id; }
  void invert() { std::swap(_tail, _head); }
  friend std::ostream &operator<<(std::ostream &, const Edge &);

private:
  int id;
  bool used = false;
  bool occupied = false;
  bool interlaced = false;
  scalar_t length, orig_length;
  Node *_tail, *_head;
};

#endif // EDGE_H_
