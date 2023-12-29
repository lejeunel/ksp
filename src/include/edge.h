#ifndef EDGE_H_
#define EDGE_H_
#include "misc.h"

class Node;

class Edge {
public:
  int occupied;
  scalar_t length, positivized_length;
  Node *origin_node, *terminal_node;

  // These fields are used for the linked list of a node's leaving
  // edge list. We have to do insertions / deletions.
  Edge *next_leaving_edge, *pred_leaving_edge;

  inline void invert();
};


#endif // EDGE_H_
