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
  void add_leaving_edge(EdgePtr);
  void del_leaving_edge(EdgePtr);
  EdgeList get_out_edges();
  void set_predecessor(NodePtr const &n) { predecessor = n; }
  NodePtr get_predecessor() { return predecessor; }
  void set_dist_from_root(float const &d) { dist_from_root = d; }
  void set_deleted(bool const &val) { deleted = val; }
  bool is_deleted() { return deleted; }
  float get_dist_from_root() { return dist_from_root; }
  Path make_path_from_root();

private:
  int id;
  EdgeList out_edges;
  NodePtr predecessor;
  float dist_from_root;
  bool deleted;
};

#endif // NODE_H_
