#include "include/ksp.h"
#include "include/sp_common.h"

KSP::KSP(std::unique_ptr<DirectedGraph> a_graph, const int &a_source,
         const int &a_sink) {

  graph = std::move(a_graph);
  source = a_source;
  sink = a_sink;
  LOG(DEBUG) << "[KSP] Initialized KSP with source: " << source
             << " and sink: " << sink;
}

std::expected<int, std::string> KSP::run(const int &k) {
  int iter = 1;
  scalar_t curr_cost;

  if (k < 1) {
    return std::unexpected{"Provide k>=1"};
  }

  LOG(DEBUG) << "[KSP] Validating source...";
  if (validate_source() == false) {
    return std::unexpected{"source node has no leaving edges."};
  }

  auto sink_node = (*graph)[sink];

  // Compute the distance of all the nodes from the source
  // using "generic" shortest paths algorithm
  auto result = bellman_ford(*graph, source);
  if (!result) {
    return std::unexpected{result.error()};
  }

  if (k == 1) {
    auto res = make_single_source_shortest_path(*graph, source, sink);
    if (!res) {
      return std::unexpected{res.error()};
    }

    paths.push_back(res.value());
    LOG(TRACE) << paths[0];
    return 0;
  }

  while (true) {
    LOG(DEBUG) << "[KSP] iter: " << iter << "/" << k;
    // Use the current distance from the source to make all edge
    // lengths positive
    positivize_edges(*graph);
    // Fix numerical errors
    clip_all_edges(*graph, 0.);

    LOG(TRACE) << "transformed graph:";
    LOG(TRACE) << *graph;

    // run single-source non-negative weights shortest-path
    auto res_djk = dijkstra(*graph, source);

    if (!res_djk) {
      return std::unexpected{res_djk.error()};
    }

    auto res = make_single_source_shortest_path(*graph, source, sink);
    if (!res) {
      LOG(WARNING) << res.error();
      return 1;
    }
    auto path = res.value();

    // Invert all the edges along the best path
    set_edges_interlaced_on_path(*graph, path);
    set_edges_occupied_on_path(*graph, path, true);
    invert_edges_on_path(*graph, path);

    LOG(DEBUG) << "[KSP] done iter: " << iter;

    if ((validate_source() == false) && (iter < k)) {
      return std::unexpected{"Cannot continue. Reached saturation at " +
                             std::to_string(iter) + " paths."};
    }

    if (iter == k) {
      break;
    }
    ++iter;
  }

  // Put back the graph in its original state (i.e. invert edges which
  // have been inverted in the process)
  reset_all_edges(*graph);
  LOG(TRACE) << "done resetting graph";

  retrieve_all_paths();
  for (auto p : paths)
    LOG(TRACE) << p;

  set_all_edges_occupied(*graph, false);
  return 0;
}

bool KSP::validate_source() {
  auto out_edges = (*graph)[source]->get_out_edges();
  if (!out_edges) {
    return false;
  }
  return true;
}

void KSP::retrieve_all_paths() {

  auto starting_edges = (*graph)[source]->get_out_edges().value();
  for (auto e : starting_edges) {
    if (e->is_occupied()) {
      e->set_used(true);
      auto path = Path();
      path.append_edge(e->tail()->get_id(), e->head()->get_id(),
                       e->get_length());
      paths.push_back(path);
    }
  }

  LOG(TRACE) << *graph;
  for (auto &p : paths) {
    auto curr_id = p[1];

    while (curr_id != sink) {
      auto continuing_edges = (*graph)[curr_id]->get_out_edges().value();
      for (auto next_e : continuing_edges) {
        if (next_e->is_occupied() && !next_e->is_interlaced() &&
            !next_e->is_used()) {
          next_e->set_used(true);
          p.append_edge(next_e->tail()->get_id(), next_e->head()->get_id(),
                        next_e->get_length());
          curr_id = next_e->head()->get_id();
          break;
        }
      }
    }
  }
  std::sort(paths.begin(), paths.end(), compare_paths_lengths());
}
