#include "dot_parser.h"
#include "edge.h"
#include "node.h"
#include "path.h"

#ifndef GRAPH_H_
#define GRAPH_H_

class DirectedGraph {
public:
  DirectedGraph(int n_nodes, int n_edges, int *node_from, int *node_to,
                scalar_t *weights);
  DirectedGraph(DiGraphEdges const &);
  int n_nodes() { return nodes.size(); };
  NodeList get_nodes() { return nodes; };
  NodePtr operator[](const int &);
  void print();

  NodeList nodes;
  EdgeList edges;
};

#endif // GRAPH_H_
