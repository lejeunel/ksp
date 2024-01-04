#include "include/bellman_ford.h"
#include "include/easylogging++.h"
#include "include/utils.h"

BellmanFord::BellmanFord(std::unique_ptr<DirectedGraph> const &graph,
                         const int &source, bool const &a_do_topological_sort) {
  do_topological_sort = a_do_topological_sort;

  for (auto n : graph->get_nodes()) {
    auto m = std::make_shared<TreeNode>(n);
    if (n->get_id() == source) {
      m->set_dist_from_root(0);
    }
    LOG(DEBUG) << "added treenode. id: " << m->get_node()->get_id()
               << " d: " << m->get_dist_from_root();
    tree_nodes.push_back(m);
  }
}

std::expected<std::vector<int>, std::string>
BellmanFord::sort_nodes(std::unique_ptr<DirectedGraph> const &graph) {
  std::vector<int> nodes_idx;

  if (do_topological_sort) {
    LOG(INFO) << "Computing topological sort...";
    auto result = topological_sort(graph);
    nodes_idx = result.value();

  } else {
    auto nodes_idx = make_indices(graph->n_nodes());
  }

  return nodes_idx;
}

std::expected<std::vector<std::shared_ptr<TreeNode>>, std::string>
BellmanFord::run(std::unique_ptr<DirectedGraph> const &graph,
                 const int &source) {

  auto sort_result = sort_nodes(graph);
  if (!sort_result.has_value()) {
    return std::unexpected{"Could not perform topological sort."};
  }

  auto nodes_idx = sort_result.value();

  for (int i = 0; i < nodes_idx.size(); i++) {
    auto tree_node = tree_nodes[nodes_idx[i]];
    LOG(DEBUG) << "iter: " << i
               << " tree_node.node.id: " << tree_node->get_node()->get_id()
               << " d: " << tree_node->get_dist_from_root();
    for (auto e : tree_node->get_leaving_edges()) {

      LOG(DEBUG) << "edge: " << e->get_source_node()->get_id() << "->"
                 << e->get_target_node()->get_id();
      auto d = tree_node->get_dist_from_root() + e->get_length();
      LOG(DEBUG) << "d: " << d;
      auto tgt_id = e->get_target_node()->get_id();
      auto src_id = e->get_source_node()->get_id();
      if (d < tree_nodes[tgt_id]->get_dist_from_root()) {
        LOG(DEBUG) << "updating dist from root of id " << tgt_id << " to " << d;
        tree_nodes[tgt_id]->set_dist_from_root(d);
        tree_nodes[tgt_id]->set_predecessor(tree_nodes[src_id]);
      }
    }
  }
  return tree_nodes;
}
