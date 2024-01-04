#ifndef TREE_NODE_H_
#define TREE_NODE_H_
#include "easylogging++.h"
#include "node.h"
#include "path.h"

class TreeNode {
private:
  NodePtr node;
  std::shared_ptr<TreeNode> predecessor_node;
  float dist_from_root;

public:
  TreeNode(NodePtr a_node) : node(a_node), dist_from_root(FLT_MAX) {}
  void set_predecessor(std::shared_ptr<TreeNode> const &n) {
    predecessor_node = n;
  }
  std::shared_ptr<TreeNode> get_predecessor() { return predecessor_node; }
  void set_dist_from_root(float const &d) { dist_from_root = d; }
  float get_dist_from_root() { return dist_from_root; }
  NodePtr get_node() { return node; }
  EdgeList get_leaving_edges() { return node->get_leaving_edges(); }
  Path make_path_to_root() {
    LOG(DEBUG) << "making path to root from id: " << node->get_id();
    Path res;
    res.append(node->get_id());
    auto pred = get_predecessor();
    while (pred != nullptr) {
      LOG(DEBUG) << "pred id: " << pred->get_node()->get_id();
      auto id = pred->get_node()->get_id();
      res.append(id);
      LOG(DEBUG) << "append to path: " << id;
      pred = pred->get_predecessor();
    }

    res.reverse();
    return res;
  }
};
#endif // TREE_NODE_H_
