#ifndef BELLMAN_FORD_H_
#define BELLMAN_FORD_H_

#include "common.h"
#include "easylogging++.h"
#include "utils.h"
#include <expected>

class BellmanFord {

public:
  BellmanFord(GraphPtr a_graph, const int &a_source)
      : graph(a_graph), source(a_source) {}
  std::expected<std::vector<NodePtr>, std::string> run();

private:
  std::expected<std::vector<int>, std::string> sort_nodes();
  std::shared_ptr<DirectedGraph> graph;
  int source;
};
#endif // BELLMAN_FORD_H_
