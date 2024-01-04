#include "include/bellman_ford.h"
#include "include/easylogging++.h"
#include "include/utils.h"

BellmanFord::BellmanFord(std::shared_ptr<DirectedGraph> a_graph,
                         const int &source, bool const &a_do_topological_sort) {

  graph = a_graph;
  do_topological_sort = a_do_topological_sort;

  LOG(DEBUG) << "Initializing tree nodes with root " << source;
  for (auto n : graph->get_nodes()) {
    auto m = std::make_shared<TreeNode>(n);
    if (n->get_id() == source) {
      m->set_dist_from_root(0);
    }
    LOG(DEBUG) << "added treenode with id: " << m->get_node()->get_id();
    tree_nodes.push_back(m);
  }
}

std::expected<std::vector<int>, std::string> BellmanFord::sort_nodes() {
  std::vector<int> nodes_idx;

  LOG(INFO) << "Computing topological sort...";
  auto result = topological_sort(graph);
  if (result.has_value()) {
    return result.value();
  } else {
    return std::unexpected{result.error()};
  }
}

std::expected<std::vector<std::shared_ptr<TreeNode>>, std::string>
BellmanFord::run() {

  std::vector<int> nodes_order;
  if (do_topological_sort) {
    auto result = sort_nodes();
    if (!result.has_value()) {
      return std::unexpected{result.error()};
    }
    nodes_order = result.value();
  } else {
    nodes_order = make_indices(graph->n_nodes());
  }

  LOG(INFO) << "Computing shortest path tree on " << nodes_order.size()
            << " nodes...";
  for (int i = 0; i < nodes_order.size(); i++) {
    auto tree_node = tree_nodes[nodes_order[i]];
    LOG(DEBUG) << "start node: " << tree_node->get_node()->get_id()
               << " num. leaving edges: "
               << tree_node->get_leaving_edges().size()
               << " dist_from_root: " << tree_node->get_dist_from_root();
    for (auto e : tree_node->get_leaving_edges()) {

      auto d = tree_node->get_dist_from_root() + e->get_length();
      auto tgt_id = e->get_target_node()->get_id();
      auto src_id = e->get_source_node()->get_id();
      LOG(DEBUG) << "edge: " << src_id << "->" << tgt_id << " d: " << d;
      if (d < tree_nodes[tgt_id]->get_dist_from_root()) {
        LOG(DEBUG) << "iter: " << i << "updating dist from root for node "
                   << tgt_id << " to " << d;
        tree_nodes[tgt_id]->set_dist_from_root(d);
        tree_nodes[tgt_id]->set_predecessor(tree_nodes[src_id]);
      }
    }
  }
  return tree_nodes;
}
