#ifndef EDGE_H_
#define EDGE_H_
#include "common.h"
#include <memory>

class Edge {
public:
  Edge(NodePtr _source_node, NodePtr _target_node, scalar_t _length);
  NodePtr get_source_node() { return source_node; }
  NodePtr get_target_node() { return target_node; }
  scalar_t get_length() { return length; }

  inline void invert();

private:
  int occupied;
  scalar_t length, positivized_length;
  NodePtr source_node, target_node;

  // These fields are used for the linked list of a node's leaving
  // edge list. We have to do insertions / deletions.
  Edge *next_leaving_edge, *pred_leaving_edge;
};

#endif // EDGE_H_
