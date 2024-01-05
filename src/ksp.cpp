#include "include/ksp.h"
#include "include/bellman_ford.h"
#include "include/common.h"
#include "include/dijkstra.h"
#include "include/easylogging++.h"
#include <exception>

INITIALIZE_EASYLOGGINGPP

KSP::KSP(std::shared_ptr<DirectedGraph> a_graph, const int &a_source,
         const int &a_sink) {

  graph = a_graph;
  source = a_source;
  sink = a_sink;
  bfd = std::make_unique<BellmanFord>(a_graph, source);
  djk = std::make_unique<Dijkstra>(a_graph, source);
}

std::expected<std::vector<Path>, std::string> KSP::run(const int &k) {
  std::vector<Path> paths;
  int iter = 1;
  scalar_t curr_cost;

  if (k < 1) {
    return std::unexpected{"Provide k>=1"};
  }

  if (validate_source(graph, source) == false) {
    return std::unexpected{"source and/or sink are not valid nodes."};
  }

  auto sink_node = (*graph)[sink];

  // Compute the distance of all the nodes from the source
  // using "generic" shortest paths algorithm
  auto result = bfd->run();
  if (!result.has_value()) {
    return std::unexpected{result.error()};
  }
  auto curr_best_path = sink_node->make_path_from_root();

  if (k == 1) {
    paths.push_back(curr_best_path);
    return paths;
  }

  LOG(INFO) << "graph:";
  graph->print();

  while (true) {
    // Use the current distance from the source to make all edge
    // lengths positive
    update_lengths();
    // Fix numerical errors
    // clip_lengths();

    LOG(INFO) << "pre-dijkstra graph:";
    graph->print();

    // run single-source non-negative weights shortest-path
    djk->run();

    LOG(INFO) << "post-dijkstra graph:";
    graph->print();

    auto path = sink_node->make_path_from_root();
    LOG(INFO) << "dijkstra path:";
    path.print();

    // Invert all the edges along the best path
    path.invert_edges();
    LOG(INFO) << "post-inversion graph:";
    graph->print();
    path.set_occupied(true);

    paths.push_back(path);

    ++iter;
    if (iter > k) {
      break;
    }

    LOG(INFO) << "k: " << iter << " shortest-path cost: " << path.get_length();
  }

  return paths;
}

bool KSP::validate_source(std::shared_ptr<DirectedGraph> graph,
                          const int &source) {
  if ((*graph)[source]->out_edges.size() > 0) {
    LOG(DEBUG) << "source node is valid";
    return true;
  }
  return false;
}

void KSP::update_lengths() {
  for (auto n : graph->nodes) {
    for (auto e : n->out_edges) {
      e->length +=
          e->source_node->dist_from_root - e->target_node->dist_from_root;
    }
  }
}

void KSP::clip_lengths() {
  for (auto n : graph->nodes) {
    for (auto e : n->out_edges) {
      if (e->length < 0) {
        e->length = 0.0;
      }
    }
  }
}
