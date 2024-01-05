#ifndef NODE_H_
#define NODE_H_
#include "common.h"
#include "path.h"

class Node {
public:
  Node(int const &a_id) : id(a_id), deleted(false), dist_from_root(FLT_MAX) {}
  Node(Node const &n) {
    id = n.id;
    dist_from_root = n.dist_from_root;
    deleted = n.deleted;
    predecessor = n.predecessor;
    out_edges = n.out_edges;
  }
  int get_id();
  EdgePtr get_out_edge(const int &adj_id);
  void add_out_edge(EdgePtr const &);
  void add_in_edge(EdgePtr);
  void del_out_edge(EdgePtr);
  Path make_path_from_root();

  int id;
  EdgeList out_edges;
  EdgeList in_edges;
  NodePtr predecessor;
  float dist_from_root;
  bool deleted;
};

#endif // NODE_H_
