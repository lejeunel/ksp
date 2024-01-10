#ifndef EDGE_H_
#define EDGE_H_
#include "common.h"
#include "node.h"
#include <memory>
#include <string>

class Edge {
public:
  Edge(int const &a_id, Node *a_source_node, Node *a_target_node,
       scalar_t _length);
  Edge(Edge *e);
  Node *tail() { return source_node; }
  Node *head() { return target_node; }
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
  void invert() { std::swap(source_node, target_node); }
  friend std::ostream &operator<<(std::ostream &, const Edge &);

private:
  int id;
  bool used = false;
  bool occupied = false;
  bool interlaced = false;
  scalar_t length, orig_length;
  Node *source_node, *target_node;
};

#endif // EDGE_H_
