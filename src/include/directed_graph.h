#ifndef GRAPH_H_
#define GRAPH_H_

#include "dot_parser.h"
#include "easylogging++.h"
#include "node.h"
#include <functional>
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
  const std::vector<std::unique_ptr<Node>> &nodes() { return _nodes; }
  const std::vector<std::unique_ptr<Edge>> &edges() { return _edges; }
  const std::vector<std::unique_ptr<Edge>> &const_edges() const {
    return _edges;
  }
  const std::expected<std::vector<Edge *>, std::string>
  const_out_edges(const int &from) const {
    return _nodes[from]->get_out_edges();
  }
  int invert_edge(const int &edge_id);

  std::string to_str() const;
  const int num_of_nodes() const { return _nodes.size(); }

private:
  void init(int n_nodes, int n_edges, int *node_from, int *node_to,
            scalar_t *weights);
  std::vector<std::unique_ptr<Node>> _nodes;
  std::vector<std::unique_ptr<Edge>> _edges;
};

#endif // GRAPH_H_
