#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#include "common.h"
#include "directed_graph.h"
#include "min_priority_queue.h"
#include "utils.h"
#include <expected>

class Dijkstra {

public:
  Dijkstra(std::shared_ptr<DirectedGraph> graph, const int &source);
  std::expected<std::vector<NodePtr>, std::string> run();

private:
  std::shared_ptr<DirectedGraph> graph;
  int source;
};

#endif // DIJKSTRA_H_
