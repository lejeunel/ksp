#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#include "common.h"
#include "directed_graph.h"
#include "min_priority_queue.h"
#include "utils.h"
#include <expected>

class Dijkstra {

public:
  Dijkstra(std::shared_ptr<DirectedGraph> a_graph, const int &a_source)
      : graph(a_graph), source(a_source) {}
  std::expected<std::vector<NodePtr>, std::string> run();

private:
  std::shared_ptr<DirectedGraph> graph;
  int source;
};

#endif // DIJKSTRA_H_
