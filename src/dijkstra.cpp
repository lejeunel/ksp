#include "include/dijkstra.h"

std::expected<int, std::string> dijkstra(DirectedGraph &graph,
                                         const int &source) {

  LOG(DEBUG) << "[Dijkstra] Initializing distances to source...";
  Utils::initialize_distances_from_source(graph, source);
  LOG(TRACE) << graph;

  auto queue = MinPriorityQueue();
  auto visited = std::vector<uint8_t>(graph.num_of_nodes(), 0);
  queue.add_with_distance_priority(graph[source]);

  // pop each node in queue and relax
  // out_edges. If a relaxation occurs, enqueue
  // head node to queue.

  LOG(DEBUG) << "[Dijkstra] Computing distances...";
  while (!queue.is_empty()) {
    auto n = queue.extract_min();

    if (visited[n->get_id()]) {
      continue;
    }

    auto out_edges = n->get_out_edges();
    if (!out_edges) {
      continue;
    }

    for (auto e : out_edges.value()) {

      auto d = n->get_dist_from_root() + e->get_length();
      auto src = e->tail();
      auto tgt = e->head();
      if (d < tgt->get_dist_from_root()) {
        tgt->set_dist_from_root(d);
        tgt->set_predecessor(src);
        visited[n->get_id()] = 1;
        queue.add_with_distance_priority(tgt);
      }
    }
  }
  return 0;
}
