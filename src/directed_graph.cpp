#include "include/directed_graph.h"
#include "include/easylogging++.h"

DirectedGraph::DirectedGraph(int _n_nodes, int _n_edges, int *_node_from,
                             int *_node_to, scalar_t *_weights) {

  nodes.reserve(_n_nodes);
  for (int i = 0; i < _n_nodes; i++) {
    nodes.push_back(std::make_shared<Node>(i));
  }

  for (int i = 0; i < _n_edges; i++) {
    auto e_out = std::make_shared<Edge>(nodes[_node_from[i]],
                                        nodes[_node_to[i]], _weights[i], false);
    nodes[_node_from[i]]->add_out_edge(e_out);
  }
}

NodePtr DirectedGraph::operator[](const int &id) { return nodes[id]; }

void DirectedGraph::print() {
  for (auto in : nodes) {
    for (auto e : in->out_edges) {
      auto out = e->target_node;
      auto l = e->length;
      auto o = e->occupied;
      LOG(INFO) << "node: " << in->id << " / " << in << ", edge: ("
                << e->source_node->id << ", " << e->source_node << ")"
                << "->"
                << "(" << e->target_node->id << ", " << e->target_node << ")"
                << " / length: " << l << " / occup.: " << o
                << " / tgt_dist_to_root: " << e->target_node->dist_from_root;
    }
  }
}
