#ifndef EDGE_H_
#define EDGE_H_
#include "common.h"
#include <memory>
#include <string>

class Edge {
public:
  Edge(NodePtr _source_node, NodePtr _target_node, scalar_t _length,
       bool occupied);
  Edge(EdgePtr const &);

  inline void invert();

  bool occupied;
  scalar_t length, orig_length;
  NodePtr source_node, target_node;

  // These fields are used for the linked list of a node's leaving
  // edge list. We have to do insertions / deletions.
  Edge *next_leaving_edge, *pred_leaving_edge;
};

#endif // EDGE_H_
