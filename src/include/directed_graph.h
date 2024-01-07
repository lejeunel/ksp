#ifndef GRAPH_H_
#define GRAPH_H_

#include "dot_parser.h"
#include "easylogging++.h"
#include "edge.h"
#include "node.h"
#include "path.h"

class DirectedGraph {
public:
  DirectedGraph(int n_nodes, int n_edges, int *node_from, int *node_to,
                scalar_t *weights);
  DirectedGraph(DiGraphEdges const &);
  NodePtr operator[](const int &);
  friend std::ostream &operator<<(std::ostream &, const DirectedGraph &);

  NodeList nodes;
  EdgeList edges;
};

#endif // GRAPH_H_
