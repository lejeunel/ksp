#include "include/sp_common.h"

std::expected<Path, std::string>
make_single_source_shortest_path(DirectedGraph &graph, const int &start_node_id,
                                 const int &end_node_id) {
  std::vector<int> nodes;
  scalar_t length = 0;
  auto curr_node = graph[end_node_id];
  auto pred = curr_node->get_predecessor();
  nodes.push_back(end_node_id);

  while (true) {

    if (!pred && (curr_node->get_id() != start_node_id)) {
      return std::unexpected{"Could not reach node " +
                             std::to_string(end_node_id) + " from node " +
                             std::to_string(start_node_id)};
    }

    auto edge = pred.value()->get_out_edge(curr_node->get_id());
    nodes.push_back(pred.value()->get_id());

    length += edge->get_length();
    if (pred.value()->get_id() == start_node_id) {
      break;
    }
    curr_node = pred.value();

    pred = curr_node->get_predecessor();
  }

  std::reverse(nodes.begin(), nodes.end());
  return Path(nodes, length);
}

void initialize_distances_from_source(DirectedGraph &graph,
                                      const int &source_id) {

  for (auto &n : graph.nodes()) {
    n->set_visited(false);
    if (n->get_id() == source_id) {
      n->set_dist_from_root(0);
    } else {
      n->set_dist_from_root(FLT_MAX);
    }
  }
}

void reset_all_edges(DirectedGraph &graph) {
  for (auto &e : graph.edges()) {

    if (e->is_occupied()) {
      e->reset_length();
      graph.invert_edge(e->get_id());
    }
    e->reset_length();
  }
}

void invert_edges_on_path(DirectedGraph &graph, Path &path) {
  std::vector<Edge *> to_invert;
  for (int i = 0; i < path.num_nodes() - 1; ++i) {
    auto tail = graph[path[i]];
    auto e = tail->get_out_edge(path[i + 1]);
    to_invert.push_back(e);
  }

  for (auto e : to_invert) {
    if (!e->is_interlaced()) {
      auto res = graph.invert_edge(e->get_id());
    }
  }
}

void positivize_edges(DirectedGraph &graph) {
  for (auto &e : graph.edges()) {
    auto curr_length = e->get_length();
    e->set_length(curr_length + e->tail()->get_dist_from_root() -
                  e->head()->get_dist_from_root());
  }
}

void clip_all_edges(DirectedGraph &graph, const scalar_t &min) {

  for (auto &e : graph.edges()) {
    if (e->get_length() < min) {
      e->set_length(min);
    }
  }
}
void set_all_edges_occupied(DirectedGraph &graph, const bool &val) {
  for (auto &e : graph.edges()) {
    e->set_occupied(val);
  }
}

void set_edges_occupied_on_path(DirectedGraph &graph, Path &path,
                                const bool &val) {
  for (int i = 0; i < path.num_nodes() - 1; ++i) {
    auto tail = graph[path[i]];
    auto e = tail->get_out_edge(path[i + 1]);
    e->set_occupied(val);
  }
}

void set_edges_interlaced_on_path(DirectedGraph &graph, Path &path) {
  for (int i = 0; i < path.num_nodes() - 2; ++i) {
    auto from = graph[path[i]];
    auto e = from->get_out_edge(path[i + 1]);
    if (e->is_occupied()) {
      e->set_interlaced(true);
    }
  }
}
