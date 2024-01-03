#ifndef KSP_H_
#define KSP_H_

#include "directed_graph.h"
#include "path.h"
#include <memory>
#include <expected>
#include <string>

class KSP {

public:
  KSP(std::unique_ptr<DirectedGraph> graph, int source, int sink);
  std::expected<std::vector<Path>, std::string> run(int);
  bool validate_source();


private:
  std::unique_ptr<DirectedGraph> graph;
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
