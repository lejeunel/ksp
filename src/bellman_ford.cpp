#include "include/bellman_ford.h"

std::expected<int, std::string> bellman_ford(DirectedGraph &graph,
                                             const int &source) {

  LOG(DEBUG) << "[Bellman-Ford] Initializing distances to source...";
  graph.initialize_distances_from_node(source);
  LOG(TRACE) << graph;

  LOG(DEBUG) << "[Bellman-Ford] Computing topological sort...";
  auto result_top_sort = graph.topological_sort();
  if (!result_top_sort) {
    return std::unexpected{result_top_sort.error()};
  }
  auto nodes_order = result_top_sort.value();

  LOG(DEBUG) << "[Bellman-Ford] Relaxing edges...";
  for (size_t i = 0; i < nodes_order.size(); i++) {
    graph.relax_edges_from(nodes_order[i]);
  }
  LOG(DEBUG) << "[Bellman-Ford] done.";
  return 0;
}
