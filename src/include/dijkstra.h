#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#include "common.h"
#include "directed_graph.h"
#include "min_priority_queue.h"
#include "tree_node.h"
#include "utils.h"
#include <expected>

class Dijkstra {

public:
  Dijkstra(std::shared_ptr<DirectedGraph> graph, const int &source);
  std::expected<std::vector<SPTreeNodePtr>, std::string> run();

private:
  std::shared_ptr<DirectedGraph> graph;
  std::vector<std::shared_ptr<SPTreeNode>> tree_nodes;
  int source;
};

#endif // DIJKSTRA_H_
