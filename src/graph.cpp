#include "include/graph.h"

Graph::Graph(int _n_nodes, int _n_edges, int *_node_from, int *_node_to,
               scalar_t *_weights){

  n_nodes = _n_nodes;
  n_edges = _n_edges;

  for(int i=0; i<_n_nodes; i++){
    nodes.push_back(std::make_unique<Node>(i));
  }

  for(int i=0; i<_n_edges; i++){
    auto e = std::make_shared<Edge>(nodes[_node_from[i]],
                                    nodes[_node_to[i]],
                                    _weights[i]);
    nodes[_node_from[i]]->add_leaving_edge(e);
    nodes[_node_to[i]]->add_incoming_edge(e);
  }


  }

std::shared_ptr<Node> Graph::get_node(int id){
  return nodes[id];
}
