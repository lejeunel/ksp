#ifndef EDGE_H_
#define EDGE_H_
#include "common.h"
#include <memory>
#include <string>

class Edge {
public:
  Edge(NodePtr _source_node, NodePtr _target_node, scalar_t _length);
  Edge(EdgePtr const &);
  EdgeList get_edges_at_head();

  bool used = false;
  bool occupied = false;
  bool interlaced = false;
  scalar_t length, orig_length;
  NodePtr source_node, target_node;
};

#endif // EDGE_H_
