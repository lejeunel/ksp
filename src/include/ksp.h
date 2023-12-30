#ifndef KSP_H_
#define KSP_H_

#include "graph.h"
#include "path.h"
#include <memory>

class KSP {

public:
  KSP(std::unique_ptr<Graph> graph, int source, int sink);
  std::vector<Path> run(int);
  bool validate_source();
  bool validate_sink();
  bool validate_source_sink();

private:
  std::unique_ptr<Graph> graph;
  std::shared_ptr<Node> source;
  std::shared_ptr<Node> sink;

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

#endif // KSP_H_
