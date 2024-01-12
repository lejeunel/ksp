#include "include/utils.h"
#include "include/common.h"
#include "include/edge.h"
#include "include/misc.h"

std::expected<std::vector<int>, std::string>
Utils::topological_sort(const DirectedGraph &graph) {

  auto n_nodes = graph.num_of_nodes();

  // compute in-degree of each node
  std::vector<int> indegree(n_nodes, 0);
  int tgt_id;
  for (const auto &e : graph.const_edges()) {
    tgt_id = e->head()->get_id();
    indegree[tgt_id]++;
  }

  // Initially insert elements with
  // indegree = 0
  std::vector<int> ans;
  std::queue<int> qrr;
  for (int n = 0; n < n_nodes; n++) {

    if (indegree[n] == 0) {
      qrr.push(n);
    }
  }

  int count = 0;
  while (!qrr.empty()) {
    // push those elements in queue with
    // indegree = 0
    int node = qrr.front();

    qrr.pop();
    ans.push_back(node);
    auto out_edges = graph.const_out_edges(node);
    if (out_edges) {

      for (auto &e : out_edges.value()) {
        tgt_id = e->head()->get_id();
        indegree[tgt_id]--;
        if (indegree[tgt_id] == 0) {
          qrr.push(tgt_id);
        }
      }
    }
    count++;
  }
  // Check if there was a cycle
  if (count != n_nodes) {
    return std::unexpected{"Found cycle in graph."};
  }
  return ans;
}

std::expected<Path, std::string>
Utils::make_shortest_path(DirectedGraph &graph, const int &start_node_id,
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

void Utils::initialize_distances_from_source(DirectedGraph &graph,
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

void Utils::reset_all_edges(DirectedGraph &graph) {
  for (auto &e : graph.edges()) {

    if (e->is_occupied()) {
      e->reset_length();
      graph.invert_edge(e->get_id());
    }
    e->reset_length();
  }
}

void Utils::invert_edges_on_path(DirectedGraph &graph, const Path &path) {
  std::vector<Edge *> to_invert;
  for (int i = 0; i < path.num_nodes() - 1; ++i) {
    auto tail = graph[path[i]];
    auto e = tail->get_out_edge(path[i + 1]);
    to_invert.push_back(e);
  }

  for (auto e : to_invert) {
    if (!e->is_interlaced()) {
      graph.invert_edge(e->get_id());
    }
  }
}

void Utils::positivize_edges(DirectedGraph &graph) {
  for (auto &e : graph.edges()) {
    auto curr_length = e->get_length();
    e->set_length(curr_length + e->tail()->get_dist_from_root() -
                  e->head()->get_dist_from_root());
  }
}

void Utils::clip_all_edges(DirectedGraph &graph, const scalar_t &min) {

  for (auto &e : graph.edges()) {
    if (e->get_length() < min) {
      e->set_length(min);
    }
  }
}
void Utils::set_all_edges_occupied(DirectedGraph &graph, const bool &val) {
  for (auto &e : graph.edges()) {
    e->set_occupied(val);
  }
}

void Utils::set_edges_occupied_on_path(DirectedGraph &graph, const Path &path,
                                       const bool &val) {
  for (int i = 0; i < path.num_nodes() - 1; ++i) {
    auto tail = graph[path[i]];
    auto e = tail->get_out_edge(path[i + 1]);
    e->set_occupied(val);
  }
}

void Utils::set_edges_interlaced_on_path(DirectedGraph &graph,
                                         const Path &path) {
  for (int i = 0; i < path.num_nodes() - 2; ++i) {
    auto from = graph[path[i]];
    auto e = from->get_out_edge(path[i + 1]);
    if (e->is_occupied()) {
      e->set_interlaced(true);
    }
  }
}
