#include <cmath>
#include <float.h>
#include <iostream>
#include "path.h"
#include "misc.h"
#include <memory>
#include <vector>

using namespace std;

#ifndef GRAPH_H_
#define GRAPH_H_

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
  Graph(int n_nodes, int n_edges, int *node_from, int *node_to,
        scalar_t *weights, int source, int sink); // Constructor


private:
  int n_nodes = 0;
  int n_edges = 0;

  std::unique_ptr<Node> source;
  std::unique_ptr<Node> sink;

  std::vector<std::unique_ptr<Edge>> edges;
  std::vector<std::unique_ptr<Node>> nodes;

  // For Dijkstra
  std::vector<std::unique_ptr<Node>> heap;

  // Updating the distances from the source in that order will work in
  // the original graph (which has to be a DAG)
  Node **_dp_order;

  // parameters
  bool min_cost = true;
  bool verbose = false;
  scalar_t tolerance = 0;
  scalar_t l_max = -1;
};

#endif // GRAPH_H_
