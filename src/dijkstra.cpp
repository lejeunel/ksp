#include "include/dijkstra.h"
#include "include/easylogging++.h"
#include "include/min_priority_queue.h"
#include "include/utils.h"

Dijkstra::Dijkstra(std::shared_ptr<DirectedGraph> a_graph,
                   const int &a_source) {

  graph = a_graph;
  source = a_source;
  tree_nodes = Utils::init_tree_nodes(graph, source);
}

std::expected<std::vector<SPTreeNodePtr>, std::string> Dijkstra::run() {
  auto queue = MinPriorityQueue();

  queue.add_with_distance_priority(tree_nodes[source]);

  LOG(DEBUG) << "computing Dijkstra...";
  while (!queue.is_empty()) {
    auto n = queue.extract_non_deleted_min();
    LOG(DEBUG) << "extracted node: " << n->get_id();
    for (auto e : n->get_leaving_edges()) {
      auto alt = n->get_dist_from_root() + e->get_length();
      auto tgt_id = e->get_target_node()->get_id();
      auto tgt = tree_nodes[tgt_id];
      auto tgt_dst_from_src = tgt->get_dist_from_root();
      if (alt < tgt_dst_from_src) {
        // create a copy of current target node with updated distance and
        // enqueue
        auto new_tgt = std::make_shared<SPTreeNode>(tgt->get_id(),
                                                    tgt->get_leaving_edges());
        new_tgt->set_dist_from_root(alt);
        new_tgt->set_predecessor(n);
        tree_nodes[tgt_id] = new_tgt;
        queue.add_with_distance_priority(new_tgt);

        // mark as "deleted", it will be automatically dropped on next
        // call to extract_non_deleted_min
        tgt->set_deleted();
      }
    }
  }
  LOG(INFO) << "done";
  return tree_nodes;
}
