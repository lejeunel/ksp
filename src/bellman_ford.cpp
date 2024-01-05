#include "include/bellman_ford.h"
#include "include/easylogging++.h"
#include "include/utils.h"

BellmanFord::BellmanFord(std::shared_ptr<DirectedGraph> a_graph,
                         const int &source) {

  graph = a_graph;
  tree_nodes = Utils::init_tree_nodes(a_graph, source);
}

std::expected<std::vector<int>, std::string> BellmanFord::sort_nodes() {
  std::vector<int> nodes_idx;

  auto result = Utils::topological_sort(graph);
  if (result.has_value()) {
    return result.value();
  } else {
    return std::unexpected{result.error()};
  }
}

std::expected<std::vector<SPTreeNodePtr>, std::string> BellmanFord::run() {

  LOG(INFO) << "Computing topological sort...";
  auto result = sort_nodes();
  if (!result.has_value()) {
    return std::unexpected{result.error()};
  }
  auto nodes_order = result.value();

  LOG(INFO) << "Computing shortest path tree on " << nodes_order.size()
            << " nodes...";
  for (int i = 0; i < nodes_order.size(); i++) {
    auto tree_node = tree_nodes[nodes_order[i]];
    LOG(DEBUG) << "start node: " << tree_node->get_id()
               << " num. leaving edges: "
               << tree_node->get_leaving_edges().size()
               << " dist_from_root: " << tree_node->get_dist_from_root();
    for (auto e : tree_node->get_leaving_edges()) {

      auto d = tree_node->get_dist_from_root() + e->get_length();
      auto tgt_id = e->get_target_node()->get_id();
      auto src_id = e->get_source_node()->get_id();
      LOG(DEBUG) << "edge: " << src_id << "->" << tgt_id << " d: " << d;
      if (d < tree_nodes[tgt_id]->get_dist_from_root()) {
        tree_nodes[tgt_id]->set_dist_from_root(d);
        tree_nodes[tgt_id]->set_predecessor(tree_nodes[src_id]);
        LOG(DEBUG) << "iter: " << i << " updated dist from root for node "
                   << tgt_id << " to " << d;
      }
    }
  }
  LOG(INFO) << "done";
  return tree_nodes;
}
