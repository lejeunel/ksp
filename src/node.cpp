#include "include/node.h"
#include "include/easylogging++.h"
#include "include/edge.h"
#include <algorithm>
#include <memory>
#include <vector>

int Node::get_id() { return id; }

void Node::add_out_edge(EdgePtr const &e) { out_edges.push_back(e); }

EdgePtr Node::get_out_edge(const int &adj_id) {
  for (auto e : out_edges) {
    if (e->target_node->id == adj_id) {
      return e;
    }
  }
  return nullptr;
}

std::expected<Path, std::string> Node::make_path_from_root() {
  EdgeList edge_list;
  auto pred = predecessor;
  int curr_id = id;
  while (pred != nullptr) {
    auto edge = pred->get_out_edge(curr_id);
    if (edge == nullptr) {
      return std::unexpected{"Could not reach root node."};
    }
    edge_list.push_back(edge);
    curr_id = pred->id;
    pred = pred->predecessor;
  }

  std::reverse(edge_list.begin(), edge_list.end());
  return Path(edge_list);
}

void Node::del_out_edge(EdgePtr e) {
  auto num_erased = std::erase(out_edges, e);
}

void Node::del_out_edges(const NodePtr &target_node) {
  for (auto e : out_edges) {
    if (e->target_node->id == target_node->id) {
      std::erase(out_edges, e);
    }
  }
}
