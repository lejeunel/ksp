#ifndef TREE_NODE_H_
#define TREE_NODE_H_
#include "node.h"
#include "path.h"

class SPTreeNode : public Node {
private:
  SPTreeNodePtr predecessor_node;
  float dist_from_root;
  bool deleted;

public:
  SPTreeNode(const int &a_id, const EdgeList &a_leaving_edges)
      : Node(a_id, a_leaving_edges), dist_from_root(FLT_MAX), deleted(false) {}
  void set_predecessor(SPTreeNodePtr const &n) { predecessor_node = n; }
  SPTreeNodePtr get_predecessor() { return predecessor_node; }
  void set_dist_from_root(float const &d) { dist_from_root = d; }
  void set_deleted() { deleted = true; }
  bool is_deleted() { return deleted; }
  float get_dist_from_root() { return dist_from_root; }
  Path make_path_from_root();
};
#endif // TREE_NODE_H_
