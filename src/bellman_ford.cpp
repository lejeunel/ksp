#include "include/bellman_ford.h"
#include "include/sp_common.h"

std::expected<int, std::string> bellman_ford(DirectedGraph &graph,
                                             const int &source) {

  LOG(DEBUG) << "[Bellman-Ford] Initializing distances to source...";
  initialize_distances_from_source(graph, source);
  LOG(TRACE) << graph;

  LOG(DEBUG) << "[Bellman-Ford] Computing topological sort...";
  auto result_top_sort = Utils::topological_sort(graph);
  if (!result_top_sort.has_value()) {
    return std::unexpected{result_top_sort.error()};
  }
  auto nodes_order = result_top_sort.value();

  LOG(DEBUG) << "[Bellman-Ford] Computing distances...";
  for (int i = 0; i < nodes_order.size(); i++) {
    auto node = graph[nodes_order[i]];

    auto out_edges = node->get_out_edges();
    if (!out_edges.has_value()) {
      continue;
    }

    for (auto e : out_edges.value()) {

      auto d = node->get_dist_from_root() + e->get_length();
      auto src = e->tail();
      auto tgt = e->head();
      if (d < tgt->get_dist_from_root()) {
        tgt->set_dist_from_root(d);
        tgt->set_predecessor(src);
      }
    }
  }
  LOG(DEBUG) << "[Bellman-Ford] done.";
  return 0;
}
