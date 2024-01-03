#include <cmath>
#include <cstdint>
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
  std::vector<std::shared_ptr<Edge>> operator[](const int&);
  bool has_cycle();
  bool dfs_check_cycle_from_node(const int& node_idx, std::vector<uint8_t>& visited,
                                              std::vector<uint8_t> visited_in_path);


private:
  int n_nodes = 0;
  int n_edges = 0;

  std::vector<std::shared_ptr<Edge>> edges;
  std::vector<std::shared_ptr<Node>> nodes;

};

#endif // GRAPH_H_
