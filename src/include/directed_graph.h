#include "edge.h"
#include "node.h"
#include "path.h"

#ifndef GRAPH_H_
#define GRAPH_H_

class DirectedGraph {
public:
  DirectedGraph(int n_nodes, int n_edges, int *node_from, int *node_to,
                scalar_t *weights); // Constructor
  int n_nodes() { return nodes.size(); };
  NodeList get_nodes() { return nodes; };
  void set_node(NodePtr n) { nodes[n->get_id()] = n; };
  NodePtr operator[](const int &);

  EdgeList edges;
  NodeList nodes;
};

#endif // GRAPH_H_
