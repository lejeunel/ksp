#include "include/bellman_ford.h"

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

  LOG(DEBUG) << "[Bellman-Ford] Initializing distances to source...";
  for (auto n : graph->nodes) {
    n->dist_from_root = FLT_MAX;
  }
  graph->nodes[source]->dist_from_root = 0.;

  LOG(DEBUG) << "[Bellman-Ford] Computing topological sort...";
  auto result = sort_nodes();
  if (!result.has_value()) {
    return std::unexpected{result.error()};
  }
  auto nodes_order = result.value();

  LOG(DEBUG) << "[Bellman-Ford] Computing distances...";
  for (int i = 0; i < nodes_order.size(); i++) {
    auto node = (*graph)[nodes_order[i]];
    for (auto e : node->out_edges) {

      auto d = node->dist_from_root + e->length;
      auto src = e->source_node.lock();
      auto tgt = e->target_node.lock();
      if (d < tgt->dist_from_root) {
        tgt->dist_from_root = d;
        tgt->predecessor = src;
      }
    }
  }
  return graph->nodes;
}
