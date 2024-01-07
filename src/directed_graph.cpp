#include "include/directed_graph.h"
#include <set>

DirectedGraph::DirectedGraph(int _n_nodes, int _n_edges, int *_node_from,
                             int *_node_to, scalar_t *_weights) {

  nodes.reserve(_n_nodes);
  for (int i = 0; i < _n_nodes; i++) {
    nodes.push_back(std::make_shared<Node>(i));
  }

  for (int i = 0; i < _n_edges; i++) {
    auto e_out = std::make_shared<Edge>(nodes[_node_from[i]],
                                        nodes[_node_to[i]], _weights[i]);
    nodes[_node_from[i]]->add_out_edge(e_out);
    edges.push_back(e_out);
    LOG(TRACE) << "[GRAPH] added edge " << e_out->source_node.lock()->id
               << " -> " << e_out->target_node.lock()->id
               << " length: " << e_out->length;
  }
}

DirectedGraph::DirectedGraph(DiGraphEdges const &edges_to_add) {

  std::set<int> node_ids;
  for (auto e : edges_to_add) {
    node_ids.insert(e.in_node);
    node_ids.insert(e.out_node);
  }

  for (auto n : node_ids) {
    nodes.push_back(std::make_shared<Node>(n));
  }

  for (auto e : edges_to_add) {
    auto e_out =
        std::make_shared<Edge>(nodes[e.in_node], nodes[e.out_node], e.weight);
    nodes[e.in_node]->add_out_edge(e_out);
    edges.push_back(e_out);
    LOG(TRACE) << "[GRAPH] added edge " << e_out->source_node.lock()->id
               << " -> " << e_out->target_node.lock()->id
               << " length: " << e_out->length;
  }
}

NodePtr DirectedGraph::operator[](const int &id) { return nodes[id]; }

std::ostream &operator<<(std::ostream &os, const DirectedGraph &graph) {
  for (auto e : graph.edges) {
    auto out = e->target_node;
    auto l = e->length;
    auto o = e->occupied;
    auto i = e->interlaced;
    os << e->source_node.lock()->id << "->" << e->target_node.lock()->id
       << " / len: " << l << " / occ: " << o << " / itl: " << i
       << " / dst: " << e->target_node.lock()->dist_from_root << std::endl;
  }
  return os;
}
