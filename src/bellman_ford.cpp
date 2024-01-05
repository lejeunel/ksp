#include "include/bellman_ford.h"
#include "include/common.h"
#include "include/easylogging++.h"
#include "include/utils.h"

BellmanFord::BellmanFord(std::shared_ptr<DirectedGraph> a_graph,
                         const int &source) {

  graph = a_graph;
  (*graph)[source]->dist_from_root = 0;
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

std::expected<NodeList, std::string> BellmanFord::run() {

  LOG(INFO) << "Computing topological sort...";
  auto result = sort_nodes();
  if (!result.has_value()) {
    return std::unexpected{result.error()};
  }
  auto nodes_order = result.value();

  LOG(INFO) << "Computing shortest path tree on " << nodes_order.size()
            << " nodes...";
  for (int i = 0; i < nodes_order.size(); i++) {
    auto node = (*graph)[nodes_order[i]];
    LOG(DEBUG) << "start node: " << node->get_id()
               << " num. leaving edges: " << node->out_edges.size()
               << " dist_from_root: " << node->dist_from_root;
    for (auto e : node->out_edges) {

      auto d = node->dist_from_root + e->length;
      auto src = e->source_node;
      auto tgt = e->target_node;
      LOG(DEBUG) << "edge: " << src->get_id() << "->" << tgt->get_id()
                 << " d: " << d;
      if (d < tgt->dist_from_root) {
        tgt->dist_from_root = d;
        tgt->predecessor = src;
        LOG(DEBUG) << "iter: " << i << " updated dist from root for node "
                   << tgt->get_id() << " to " << d;
      }
    }
  }
  LOG(INFO) << "done";
  return graph->get_nodes();
}
