#ifndef KSP_H_
#define KSP_H_

#include "bellman_ford.h"
#include "common.h"
#include "dijkstra.h"
#include "directed_graph.h"
#include "path.h"
#include <expected>
#include <string>

class KSP {

public:
  KSP(std::shared_ptr<DirectedGraph> graph, const int &source, const int &sink);
  std::expected<std::vector<Path>, std::string> run(const int &);
  bool validate_source(std::shared_ptr<DirectedGraph> graph, const int &source);
  void update_lengths();
  void clip_lengths();

private:
  int source;
  int sink;
  std::unique_ptr<BellmanFord> bfd;
  std::unique_ptr<Dijkstra> djk;
  std::shared_ptr<DirectedGraph> graph;

  // parameters
  bool min_cost = false;
  int K = 1;
};

#endif // KSP_H_
