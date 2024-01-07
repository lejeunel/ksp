#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#include "common.h"
#include "directed_graph.h"
#include "easylogging++.h"
#include "min_priority_queue.h"
#include "utils.h"
#include <expected>

class Dijkstra {

public:
  Dijkstra(GraphPtr a_graph, const int &a_source)
      : graph(a_graph), source(a_source) {}
  std::expected<std::vector<NodePtr>, std::string> run();

private:
  GraphPtr graph;
  int source;
};

#endif // DIJKSTRA_H_
