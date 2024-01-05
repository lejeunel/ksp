#include "include/node.h"
#include "include/easylogging++.h"
#include "include/edge.h"
#include <algorithm>
#include <memory>
#include <vector>

int Node::get_id() { return id; }

void Node::add_out_edge(EdgePtr const &e) {

  LOG(DEBUG) << "appending out edge: (" << e->source_node->id << ", "
             << e->source_node << "->"
             << "(" << e->target_node->id << ", " << e->target_node << ")";
  out_edges.push_back(e);
}

void Node::add_in_edge(EdgePtr e) {

  LOG(DEBUG) << "appending in edge: (" << e->source_node->id << ", "
             << e->source_node << "->"
             << "(" << e->target_node->id << ", " << e->target_node << ")";
  in_edges.push_back(e);
}

EdgePtr Node::get_out_edge(const int &adj_id) {
  for (auto e : out_edges) {
    if (e->target_node->id == adj_id) {
      return e;
    }
  }
  return nullptr;
}

Path Node::make_path_from_root() {
  EdgeList edge_list;
  LOG(DEBUG) << "making path from " << id << " to root";
  auto pred = predecessor;
  int curr_id = id;
  while (pred != nullptr) {
    auto edge = pred->get_out_edge(curr_id);
    edge_list.push_back(edge);
    curr_id = pred->id;
    pred = pred->predecessor;
  }
  LOG(DEBUG) << "done";

  std::reverse(edge_list.begin(), edge_list.end());
  return Path(edge_list);
}

void Node::del_out_edge(EdgePtr e) {
  auto num_erased = std::erase(out_edges, e);
  LOG(DEBUG) << "deleted " << num_erased << " out edge from node " << id;
}
