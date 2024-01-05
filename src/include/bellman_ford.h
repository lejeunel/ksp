#ifndef BELLMAN_FORD_H_
#define BELLMAN_FORD_H_

#include "common.h"
#include "directed_graph.h"
#include <expected>

class BellmanFord {

public:
  BellmanFord(std::shared_ptr<DirectedGraph> graph, const int &source);
  std::expected<std::vector<NodePtr>, std::string> run();
  Path generate_path_to_root(const int &start);

private:
  std::expected<std::vector<int>, std::string> sort_nodes();
  std::shared_ptr<DirectedGraph> graph;
};
#endif // BELLMAN_FORD_H_
