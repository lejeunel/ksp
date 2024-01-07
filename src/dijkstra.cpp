#include "include/dijkstra.h"

std::expected<NodeList, std::string> Dijkstra::run() {

  LOG(DEBUG) << "[Dijkstra] Initializing distances to source...";
  for (auto n : graph->nodes) {
    n->dist_from_root = FLT_MAX;
  }
  graph->nodes[source]->dist_from_root = 0.;

  auto queue = MinPriorityQueue();
  auto visited = std::vector<uint8_t>(graph->get_nodes().size(), 0);
  queue.add_with_distance_priority((*graph)[source]);

  LOG(DEBUG) << "[Dijkstra] Computing distances...";
  while (!queue.is_empty()) {
    auto n = queue.extract_min();

    if (visited[n->id]) {
      continue;
    }

    for (auto e : n->out_edges) {
      auto alt = n->dist_from_root + e->length;
      auto tgt = e->target_node;
      auto tgt_dst_from_src = tgt->dist_from_root;
      if (alt < tgt_dst_from_src) {
        // create a copy of current target node with updated distance and
        // enqueue
        tgt->dist_from_root = alt;
        tgt->predecessor = n;
        visited[n->get_id()] = 1;
        queue.add_with_distance_priority(tgt);
      }
    }
  }
  return graph->get_nodes();
}
