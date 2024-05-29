#ifndef GRAPH_H_
#define GRAPH_H_

#include "dot_parser.h"
#include "easylogging++.h"
#include "node.h"
#include <functional>
#include <queue>
#include <ranges>
#include <vector>

class Path;
class Edge;

class DirectedGraph {
public:
  DirectedGraph(int n_nodes, int n_edges, int *node_from, int *node_to,
                scalar_t *weights);
  DirectedGraph(DiGraphEdges const &);
  friend std::ostream &operator<<(std::ostream &, const DirectedGraph &);
  Node *operator[](const int &id) { return _nodes[id].get(); }
  auto &nodes() { return _nodes; }
  auto &edges() { return _edges; }
  const auto &const_edges() const { return _edges; }
  const std::expected<std::vector<Edge *>, std::string>
  const_out_edges(const int &from) const {
    return _nodes[from]->get_out_edges();
  }
  void invert_edge(const int &edge_id);
  void positivize_edges();
  void clip_all_edges();
  void set_all_edges_occupied(const bool &val);
  void reset_all_edges();
  void initialize_distances_from_node(const int &node_id);
  std::expected<std::vector<int>, std::string> topological_sort();
  void set_edges_occupied_on_path(const Path &p, const bool &val);
  void set_edges_interlaced_on_path(const Path &p);
  void invert_edges_on_path(const Path &p);
  std::expected<Path, std::string> make_shortest_path(const int &start_node_id,
                                                      const int &end_node_id);
  std::vector<int> relax_edges_from(const int &node_id);

  std::string to_str() const;
  int num_of_nodes() const { return _nodes.size(); }
  bool compare_dist_from_root(const int &first_node_id,
                              const int &second_node_id) const;

private:
  void init(int n_nodes, int n_edges, int *node_from, int *node_to,
            scalar_t *weights);
  std::vector<std::unique_ptr<Node>> _nodes;
  std::vector<std::unique_ptr<Edge>> _edges;
};

#endif // GRAPH_H_
