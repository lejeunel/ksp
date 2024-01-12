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
