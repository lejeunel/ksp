#include "include/ksp.h"
#include "include/bellman_ford.h"
#include "include/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

KSP::KSP(std::shared_ptr<DirectedGraph> a_graph, const int &a_source,
         const int &a_sink) {

  graph = a_graph;
  source = a_source;
  sink = a_sink;
  bfd = std::make_unique<BellmanFord>(a_graph, source);
}

std::expected<std::vector<Path>, std::string> KSP::run() {
  if (validate_source(graph, source) == false) {
    return std::unexpected{"source and/or sink are not valid nodes."};
  }

  auto bf_result = bfd->run();
  if (!bf_result.has_value()) {
    return std::unexpected{bf_result.error()};
  }

  auto path = bf_result.value()[sink]->make_path_from_root();
  std::vector<Path> res;
  res.push_back(path);
  return res;
}

bool KSP::validate_source(std::shared_ptr<DirectedGraph> graph,
                          const int &source) {
  if (graph->get_node(source)->get_leaving_edges().size() > 0) {
    LOG(DEBUG) << "source node is valid";
    return true;
  }
  return false;
}
