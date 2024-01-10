#ifndef NODE_H_
#define NODE_H_
#include "common.h"
#include "easylogging++.h"
#include <algorithm>
#include <expected>
#include <memory>
#include <vector>

class Edge;

class Node {
public:
  Node(int const &a_id) : id(a_id) {}
  // Node(Node const &n);
  int get_id() const { return id; }

  void set_dist_from_root(scalar_t const &dist) { dist_from_root = dist; }
  const scalar_t get_dist_from_root() const { return dist_from_root; }
  std::expected<Node *, std::string> get_predecessor() const {
    if (predecessor == nullptr) {
      return std::unexpected{"Could not find predecessor node"};
    }
    return predecessor;
  }
  void set_predecessor(Node *n) { predecessor = n; }
  void set_visited(const bool &val) { visited = val; }
  bool is_visited() const { return visited; }
  void add_out_edge(Edge *e) { out_edges.push_back(e); }
  int del_out_edge(const int &edge_id);

  Edge *get_out_edge(const int &adj_id) const;
  std::expected<std::vector<Edge *>, std::string> get_out_edges() const;

private:
  int id;
  bool visited = false;
  std::vector<Edge *> out_edges;
  Node *predecessor = nullptr;
  scalar_t dist_from_root;
};

#endif // NODE_H_
