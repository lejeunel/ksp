#ifndef KSP_H_
#define KSP_H_

#include "bellman_ford.h"
#include "common.h"
#include "dijkstra.h"
#include "directed_graph.h"
#include "path.h"
#include <exception>
#include <expected>
#include <string>

class KSP {

public:
  KSP(std::unique_ptr<DirectedGraph> graph, const int &source, const int &sink);
  std::expected<std::vector<Path>, std::string> run(const int &);
  bool validate_source();
  void update_lengths();
  void retrieve_all_paths();
  std::vector<Path> get_paths() { return paths; }

private:
  int source;
  int sink;
  std::unique_ptr<DirectedGraph> graph;
  std::vector<Path> paths;

  // parameters
  bool min_cost = false;
  int K = 1;
};

#endif // KSP_H_
