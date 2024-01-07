#include "include/ksp.h"

KSP::KSP(std::shared_ptr<DirectedGraph> a_graph, const int &a_source,
         const int &a_sink) {

  graph = a_graph;
  source = a_source;
  sink = a_sink;
  bfd = std::make_unique<BellmanFord>(a_graph, source);
  djk = std::make_unique<Dijkstra>(a_graph, source);
  LOG(DEBUG) << "[KSP] Initialized KSP with source: " << source
             << " and sink: " << sink;
}

std::expected<PathList, std::string> KSP::run(const int &k) {
  int iter = 1;
  scalar_t curr_cost;

  if (k < 1) {
    return std::unexpected{"Provide k>=1"};
  }

  if (validate_source(graph, source) == false) {
    return std::unexpected{"[KSP] source is not valid nodes."};
  }

  auto sink_node = (*graph)[sink];

  // Compute the distance of all the nodes from the source
  // using "generic" shortest paths algorithm
  auto result = bfd->run();
  if (!result.has_value()) {
    return std::unexpected{result.error()};
  }

  if (k == 1) {
    auto res = sink_node->make_path_from_root();
    if (!res.has_value()) {
      return std::unexpected{res.error()};
    }

    auto first_path = std::make_shared<Path>();
    paths.push_back(std::make_shared<Path>(res.value()));
    LOG(DEBUG) << *paths[0];
    return paths;
  }

  while (true) {
    LOG(DEBUG) << "[KSP] iter. " << iter << "/" << k;
    // Use the current distance from the source to make all edge
    // lengths positive
    update_lengths();
    // Fix numerical errors
    clip_lengths();

    LOG(TRACE) << "transformed graph:";
    LOG(TRACE) << *graph;

    // run single-source non-negative weights shortest-path
    djk->run();

    auto res = sink_node->make_path_from_root();
    if (!res.has_value()) {
      LOG(WARNING) << res.error();
      break;
    }

    auto path = res.value();

    // Invert all the edges along the best path
    set_interlaced_on_path(path);
    invert_edges_on_path(path);
    path.set_occupied(true);

    ++iter;

    if (iter > k) {
      break;
    }
  }

  // Put back the graph in its original state (i.e. invert edges which
  // have been inverted in the process)
  reset_all_inverted_edges();

  retrieve_all_paths();

  reset_all_occupied_edges();
  return paths;
}

bool KSP::validate_source(std::shared_ptr<DirectedGraph> graph,
                          const int &source) {
  if ((*graph)[source]->out_edges.size() > 0) {
    LOG(DEBUG) << "[KSP] Found leaving edges from source node";
    return true;
  }
  return false;
}

void KSP::update_lengths() {
  for (auto n : graph->nodes) {
    for (auto e : n->out_edges) {
      e->length += e->source_node.lock()->dist_from_root -
                   e->target_node.lock()->dist_from_root;
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
void KSP::invert_edge(EdgePtr const &e) {

  e->length = -e->length;
  e->source_node.lock()->del_out_edge(e);

  auto orig_tgt = e->target_node;

  (e->source_node).swap(e->target_node);
  orig_tgt.lock()->add_out_edge(e);
}

void KSP::invert_edges_on_path(Path &p) {
  for (auto e : p.get_edges()) {
    if (!e->interlaced) {
      invert_edge(e);
    }
  }
}

void KSP::set_interlaced_on_path(Path &p) {
  for (auto e : p.get_edges()) {
    if (e->occupied) {
      e->interlaced = true;
    }
  }
}

void KSP::reset_all_inverted_edges() {

  for (auto e : graph->edges) {
    if (e->occupied) {
      invert_edge(e);
    }
    e->length = e->orig_length;
  }
}

void KSP::reset_all_occupied_edges() {

  for (auto e : graph->edges) {
    if (e->occupied) {
      e->occupied = false;
    }
  }
}

void KSP::retrieve_all_paths() {

  for (auto e : graph->nodes[source]->out_edges) {
    if (e->occupied) {
      e->used = true;
      auto path = std::make_shared<Path>(e);
      paths.push_back(path);
    }
  }

  for (auto p : paths) {
    auto e = (*p)[0];
    while (e->target_node.lock() != graph->nodes[sink]) {
      for (auto next_e : e->get_edges_at_head()) {
        if ((next_e->occupied) && (!next_e->interlaced) && (!next_e->used)) {
          next_e->used = true;
          p->append_edge(next_e);
          e = next_e;
          break;
        }
      }
    }
    // p->print();
  }

  std::sort(paths.begin(), paths.end(), compare_paths_lengths());
}
