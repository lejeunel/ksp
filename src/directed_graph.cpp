#include "include/directed_graph.h"
#include "include/edge.h"
#include "include/path.h"
#include <set>
#include <sstream>

void DirectedGraph::init(int _n_nodes, int _n_edges, int *_node_from,
                         int *_node_to, scalar_t *_weights) {
  _nodes.reserve(_n_nodes);
  for (int i = 0; i < _n_nodes; i++) {
    _nodes.push_back(std::make_unique<Node>(i));
  }

  for (int i = 0; i < _n_edges; i++) {
    _edges.push_back(std::make_unique<Edge>(i, _nodes[_node_from[i]].get(),
                                            _nodes[_node_to[i]].get(),
                                            _weights[i]));
    _nodes[_node_from[i]]->add_out_edge(_edges.back().get());
  }
}

DirectedGraph::DirectedGraph(int _n_nodes, int _n_edges, int *_node_from,
                             int *_node_to, scalar_t *_weights) {
  init(_n_nodes, _n_edges, _node_from, _node_to, _weights);
}

DirectedGraph::DirectedGraph(DiGraphEdges const &edges_to_add) {

  std::set<int> node_ids;
  std::vector<int> nodes_from;
  std::vector<int> nodes_to;
  std::vector<scalar_t> weights;
  for (auto e : edges_to_add) {
    node_ids.insert(e.in_node);
    node_ids.insert(e.out_node);
    nodes_from.push_back(e.in_node);
    nodes_to.push_back(e.out_node);
    weights.push_back(e.weight);
  }

  init(node_ids.size(), edges_to_add.size(), nodes_from.data(), nodes_to.data(),
       weights.data());
}

std::string DirectedGraph::to_str() const {

  std::stringstream s;
  for (auto &e : const_edges()) {
    auto len = e->get_length();
    auto occ = e->is_occupied();
    auto itl = e->is_interlaced();
    s << "(" << e->get_id() << ") " << e->tail()->get_id() << "->"
      << e->head()->get_id() << " / len: " << len << " / occ: " << occ
      << " / itl: " << itl
      << " head_dst_from_root: " << e->head()->get_dist_from_root()
      << std::endl;
  }
  return s.str();
};

std::ostream &operator<<(std::ostream &os, const DirectedGraph &graph) {
  os << graph.to_str();
  return os;
}

void DirectedGraph::invert_edge(const int &edge_id) {
  auto e = _edges[edge_id].get();
  auto tail = e->tail();
  auto head = e->head();
  tail->del_out_edge(e->get_id());
  head->add_out_edge(e);
  e->invert();
}

void DirectedGraph::positivize_edges() {

  for (auto &e : _edges) {
    auto curr_length = e->get_length();
    e->set_length(curr_length + e->tail()->get_dist_from_root() -
                  e->head()->get_dist_from_root());
  }
}

void DirectedGraph::clip_all_edges() {

  for (auto &e : _edges) {
    if (e->get_length() < 0.) {
      e->set_length(0.);
    }
  }
}

void DirectedGraph::set_all_edges_occupied(const bool &val) {
  for (auto &e : _edges) {
    e->set_occupied(val);
  }
}

void DirectedGraph::reset_all_edges() {
  for (auto &e : _edges) {

    if (e->is_occupied()) {
      e->reset_length();
      invert_edge(e->get_id());
    }
    e->reset_length();
  }
}

void DirectedGraph::initialize_distances_from_node(const int &node_id) {

  for (auto &n : _nodes) {
    n->set_visited(false);
    if (n->get_id() == node_id) {
      n->set_dist_from_root(0);
    } else {
      n->set_dist_from_root(FLT_MAX);
    }
  }
}

std::expected<std::vector<int>, std::string> DirectedGraph::topological_sort() {

  auto n_nodes = num_of_nodes();

  // compute in-degree of each node
  std::vector<int> indegree(n_nodes, 0);
  int tgt_id;
  for (const auto &e : const_edges()) {
    tgt_id = e->head()->get_id();
    indegree[tgt_id]++;
  }

  // Initially insert elements with
  // indegree = 0
  std::vector<int> sorted_nodes_id;
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
    sorted_nodes_id.push_back(node);
    auto out_edges = const_out_edges(node);
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
  return sorted_nodes_id;
}

void DirectedGraph::set_edges_occupied_on_path(const Path &path,
                                               const bool &val) {
  for (int i = 0; i < path.num_nodes() - 1; ++i) {
    auto tail = _nodes[path[i]].get();
    auto e = tail->get_out_edge(path[i + 1]);
    e->set_occupied(val);
  }
}

void DirectedGraph::set_edges_interlaced_on_path(const Path &path) {
  for (int i = 0; i < path.num_nodes() - 2; ++i) {
    auto from = _nodes[path[i]].get();
    auto e = from->get_out_edge(path[i + 1]);
    if (e->is_occupied()) {
      e->set_interlaced(true);
    }
  }
}

void DirectedGraph::invert_edges_on_path(const Path &path) {
  std::vector<Edge *> to_invert;
  for (int i = 0; i < path.num_nodes() - 1; ++i) {
    auto tail = _nodes[path[i]].get();
    auto e = tail->get_out_edge(path[i + 1]);
    to_invert.push_back(e);
  }

  for (auto e : to_invert) {
    if (!e->is_interlaced()) {
      invert_edge(e->get_id());
    }
  }
}

std::expected<Path, std::string>
DirectedGraph::make_shortest_path(const int &start_node_id,
                                  const int &end_node_id) {
  std::vector<int> nodes;
  scalar_t length = 0;
  auto curr_node = _nodes[end_node_id].get();
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

void DirectedGraph::relax_edges_from(const int &node_id) {
  Node *node = _nodes[node_id].get();

  auto out_edges = node->get_out_edges();
  if (!out_edges) {
    return;
  }

  for (auto e : out_edges.value()) {

    auto d = node->get_dist_from_root() + e->get_length();
    auto src = e->tail();
    auto tgt = e->head();
    if (d < tgt->get_dist_from_root()) {
      tgt->set_dist_from_root(d);
      tgt->set_predecessor(src);
    }
  }
}
