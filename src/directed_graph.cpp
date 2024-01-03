#include "include/directed_graph.h"
#include "include/easylogging++.h"
#include <iostream>

DirectedGraph::DirectedGraph(int _n_nodes, int _n_edges, int *_node_from,
                             int *_node_to, scalar_t *_weights) {

  n_nodes = _n_nodes;
  n_edges = _n_edges;

  nodes.reserve(_n_nodes);
  for (int i = 0; i < _n_nodes; i++) {
    nodes.push_back(std::make_shared<Node>(i));
  }

  for (int i = 0; i < _n_edges; i++) {
    auto e = std::make_shared<Edge>(nodes[_node_from[i]], nodes[_node_to[i]],
_weights[i]);
    LOG(DEBUG) << "adding edge: " << e->get_source_node()->get_id() <<
      "->" << e->get_target_node()->get_id();
    nodes[_node_from[i]]->add_leaving_edge(e);
  }
}

std::shared_ptr<Node> DirectedGraph::get_node(const int &id) {
  return nodes[id];
}
std::vector<std::shared_ptr<Edge>> DirectedGraph::operator[](const int &id){
  return nodes[id]->get_leaving_edges();
}

bool DirectedGraph::dfs_check_cycle_from_node(
    const int &node_idx, std::vector<uint8_t> &visited,
    std::vector<uint8_t> visited_in_path) {

  visited[node_idx] = 1;
  visited_in_path[node_idx] = 1;


  LOG(DEBUG) << "node_idx:" << node_idx;
  auto leaving_edges = nodes[node_idx]->get_leaving_edges();
  // traverse for adjacent nodes
  for (auto e : leaving_edges) {
    auto target_node = e->get_target_node()->get_id();
    // when the node is not visited
    LOG(DEBUG) << "edge: " << e->get_source_node()->get_id() << "->" << target_node;
    LOG(DEBUG) << "visited[" << target_node << "]: " << (int)visited[target_node];
    if (!visited[target_node]) {
      LOG(DEBUG) << "visiting";
      if (dfs_check_cycle_from_node(target_node, visited,
                                    visited_in_path) == true){
        LOG(INFO) << "detected cycle at node: " << target_node;
        return true;
      }
    }
    // if the node has been previously visited
    // but it has to be visited on the same path
    else if (visited_in_path[target_node]) {
      LOG(INFO) << "detected cycle at node: " << target_node;
      return true;
    }
  }
  visited_in_path[node_idx] = 0;
  return false;
}

bool DirectedGraph::has_cycle() {
  auto visited = std::vector<uint8_t>(n_nodes, 0);
  auto visited_in_path = std::vector<uint8_t>(n_nodes, 0);

  for (auto n : nodes) {
    auto id = n->get_id();
    if (!visited[id]) {
      if (dfs_check_cycle_from_node(id, visited, visited_in_path) == true)
        return true;
    }
  }

  return false;
}
