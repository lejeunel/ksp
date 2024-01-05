#include "include/dijkstra.h"
#include "include/easylogging++.h"
#include "include/min_priority_queue.h"
#include "include/utils.h"

Dijkstra::Dijkstra(std::shared_ptr<DirectedGraph> a_graph,
                   const int &a_source) {

  graph = a_graph;
  source = a_source;
  (*graph)[source]->set_dist_from_root(0);
}

std::expected<NodeList, std::string> Dijkstra::run() {

  auto queue = MinPriorityQueue();
  queue.add_with_distance_priority((*graph)[source]);

  LOG(DEBUG) << "computing dijkstra...";
  while (!queue.is_empty()) {
    auto n = queue.extract_non_deleted_min();
    LOG(DEBUG) << "extracted node: " << n->get_id();
    for (auto e : n->get_out_edges()) {
      auto alt = n->get_dist_from_root() + e->get_length();
      auto tgt = e->get_target_node();
      auto tgt_dst_from_src = tgt->get_dist_from_root();
      LOG(DEBUG) << "new/old distance " << alt << "/" << tgt_dst_from_src
                 << " to node: " << tgt->get_id() << " from node "
                 << n->get_id();
      if (alt < tgt_dst_from_src) {
        // create a copy of current target node with updated distance and
        // enqueue
        tgt->set_dist_from_root(alt);
        tgt->set_predecessor(n);
        auto new_tgt = std::make_shared<Node>(*tgt);
        new_tgt->set_deleted(false);
        graph->set_node(new_tgt);
        queue.add_with_distance_priority(new_tgt);

        // mark original node as "deleted", it will be automatically dropped on
        // next call to extract_non_deleted_min
        tgt->set_deleted(true);
        LOG(DEBUG) << "tgt->is_deleted(): " << tgt->is_deleted();
        LOG(DEBUG) << "new_tgt->is_deleted(): " << new_tgt->is_deleted();
      }
    }
  }
  LOG(DEBUG) << "done";
  return graph->get_nodes();
}
