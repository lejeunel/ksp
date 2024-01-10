#include "include/node.h"
#include "include/edge.h"
#include <exception>

Edge *Node::get_out_edge(const int &adj_id) const {
  for (auto e : out_edges) {
    if (e->head()->get_id() == adj_id) {
      return e;
    }
  }
  return nullptr;
}

int Node::del_out_edge(const int &edge_id) {
  for (int i = 0; i < out_edges.size(); ++i) {
    if (out_edges[i]->get_id() == edge_id) {
      out_edges.erase(out_edges.begin() + i);
      return 0;
    }
  }
  return 1;
}

std::expected<std::vector<Edge *>, std::string> Node::get_out_edges() const {
  if (out_edges.size() == 0) {
    return std::unexpected{"Could not find out edges from node " +
                           std::to_string(id)};
  }

  return out_edges;
}
