#ifndef NODE_H_
#define NODE_H_
#include "common.h"

class Node {
public:
  Node(int const &);
  Node(int const &id, EdgeList const &leaving_edges);

  int get_id();
  void add_leaving_edge(EdgePtr);
  void del_leaving_edge(EdgePtr);
  EdgeList get_leaving_edges();

protected:
  int id;
  EdgeList leaving_edges;
};

#endif // NODE_H_
