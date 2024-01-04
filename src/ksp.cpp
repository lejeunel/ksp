#include "include/ksp.h"
#include "include/bellman_ford.h"
#include "include/common.h"
#include "include/path.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

KSP::KSP(const int &a_K, const bool &a_min_cost) {
  K = a_K;
  min_cost = a_min_cost;
}

KSP::KSP() {}

std::expected<std::vector<Path>, std::string>
KSP::run(std::unique_ptr<DirectedGraph> const &graph, const int &source,
         const int &sink) {
  if (validate_source(graph, source) == false) {
    return std::unexpected{"source and/or sink are not valid nodes."};
  }

  auto bf = BellmanFord(graph, source, true);

  auto bf_result = bf.run(graph, source);
  if (!bf_result.has_value()) {
    return std::unexpected{bf_result.error()};
  }

  auto path = bf_result.value()[sink]->make_path_to_root();
  std::vector<Path> res;
  res.push_back(path);
  return res;
}

bool KSP::validate_source(std::unique_ptr<DirectedGraph> const &graph,
                          const int &source) {
  if ((*graph)[source].size() > 0) {
    return true;
  }
  return false;
}
