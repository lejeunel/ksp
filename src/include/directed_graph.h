#include <cmath>
#include <float.h>
#include <iostream>
#include "path.h"
#include "misc.h"
#include <memory>
#include <vector>


#ifndef GRAPH_H_
#define GRAPH_H_

class DirectedGraph {
public:
  DirectedGraph(int n_nodes, int n_edges, int *node_from, int *node_to,
        scalar_t *weights); // Constructor
  std::shared_ptr<Node> get_node(const int&);
  bool has_cycle();
  bool dfs_check_cycle_from_node(const int& node_idx, std::vector<bool>& visited,
                                              std::vector<bool> visited_in_path);


private:
  int n_nodes = 0;
  int n_edges = 0;

  std::vector<std::shared_ptr<Edge>> edges;
  std::vector<std::shared_ptr<Node>> nodes;

};

#endif // GRAPH_H_
