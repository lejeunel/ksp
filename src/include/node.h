#ifndef NODE_H_
#define NODE_H_
#include "common.h"
#include "path.h"

class Node {
public:
  Node(int const &a_id) : id(a_id) {}
  Node(Node const &n);
  int get_id();
  EdgePtr get_out_edge(const int &adj_id);
  void add_out_edge(EdgePtr const &);
  void del_out_edge(EdgePtr);
  void del_out_edges(const NodePtr &target_node);
  Path make_path_from_root();

  int id;
  EdgeList out_edges;
  EdgeList in_edges;
  NodePtr predecessor;
  float dist_from_root;
};

#endif // NODE_H_
