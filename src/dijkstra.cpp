#include "include/dijkstra.h"

std::expected<int, std::string> dijkstra(DirectedGraph &graph,
                                         const int &source) {

  LOG(DEBUG) << "[Dijkstra] Initializing distances to source...";
  graph.initialize_distances_from_node(source);
  LOG(TRACE) << graph;

  auto queue = MinPriorityQueue(graph);
  queue.add(source);

  // pop each node in queue and relax
  // out_edges. If a relaxation occurs, enqueue
  // head node to queue.
  LOG(DEBUG) << "[Dijkstra] Computing distances...";
  while (!queue.is_empty()) {
    auto n = queue.extract_min();

    auto relaxed_target_nodes = graph.relax_edges_from(n);
    for (auto relaxed_target_node : relaxed_target_nodes) {
      queue.set_node_as_visited(n);
      queue.add(relaxed_target_node);
    }
  }
  return 0;
}
