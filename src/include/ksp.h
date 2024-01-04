#ifndef KSP_H_
#define KSP_H_

#include "common.h"
#include "directed_graph.h"
#include "path.h"
#include <expected>
#include <string>

class KSP {

public:
  KSP(const int &k, const bool &min_cost);
  KSP();
  std::expected<std::vector<Path>, std::string>
  run(std::unique_ptr<DirectedGraph> const &graph, const int &source,
      const int &sink);
  bool validate_source(std::unique_ptr<DirectedGraph> const &graph,
                       const int &source);

private:
  NodePtr source;
  NodePtr sink;

  // parameters
  bool min_cost = false;
  int K = 1;
};

#endif // KSP_H_
