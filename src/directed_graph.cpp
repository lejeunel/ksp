#include "include/directed_graph.h"
#include "include/easylogging++.h"
#include <iostream>

DirectedGraph::DirectedGraph(int _n_nodes, int _n_edges, int *_node_from,
                             int *_node_to, scalar_t *_weights) {

  nodes.reserve(_n_nodes);
  for (int i = 0; i < _n_nodes; i++) {
    nodes.push_back(std::make_shared<Node>(i));
  }

  LOG(DEBUG) << "n_edges: " << _n_edges;
  for (int i = 0; i < _n_edges; i++) {
    auto e = std::make_shared<Edge>(nodes[_node_from[i]], nodes[_node_to[i]],
                                    _weights[i]);
    LOG(DEBUG) << "adding edge: " << e->get_source_node()->get_id() << "->"
               << e->get_target_node()->get_id();
    nodes[_node_from[i]]->add_leaving_edge(e);
  }
}

NodePtr DirectedGraph::get_node(const int &id) { return nodes[id]; }
std::vector<std::shared_ptr<Edge>> DirectedGraph::operator[](const int &id) {
  return nodes[id]->get_leaving_edges();
}
