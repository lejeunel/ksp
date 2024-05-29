#include "include/dijkstra.h"

std::expected<int, std::string> dijkstra(DirectedGraph &graph,
                                         const int &source) {

  LOG(DEBUG) << "[Dijkstra] Initializing distances to source...";
  graph.initialize_distances_from_node(source);
  LOG(TRACE) << graph;

  auto queue = MinPriorityQueue(graph);
  auto visited = std::vector<uint8_t>(graph.num_of_nodes(), 0);
  queue.add_with_distance_priority(source);

  // pop each node in queue and relax
  // out_edges. If a relaxation occurs, enqueue
  // head node to queue.
  LOG(DEBUG) << "[Dijkstra] Computing distances...";
  while (!queue.is_empty()) {
    auto n = queue.extract_min();

    if (visited[n]) {
      continue;
    }

    auto relaxed_target_nodes = graph.relax_edges_from(n);
    for (auto relaxed_target_node : relaxed_target_nodes) {
      visited[n] = 1;
      queue.add_with_distance_priority(relaxed_target_node);
    }
  }
  return 0;
}
