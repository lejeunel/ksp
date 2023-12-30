#include "include/directed_graph.h"
#include "include/easylogging++.h"

DirectedGraph::DirectedGraph(int _n_nodes, int _n_edges, int *_node_from,
                             int *_node_to, scalar_t *_weights) {

  n_nodes = _n_nodes;
  n_edges = _n_edges;

  for (int i = 0; i < _n_nodes; i++) {
    nodes.push_back(std::make_unique<Node>(i));
  }

  for (int i = 0; i < _n_edges; i++) {
    auto e = std::make_shared<Edge>(nodes[_node_from[i]], nodes[_node_to[i]],
                                    _weights[i]);
    nodes[_node_from[i]]->add_leaving_edge(e);
    nodes[_node_to[i]]->add_incoming_edge(e);
  }
}

std::shared_ptr<Node> DirectedGraph::get_node(const int &id) {
  return nodes[id];
}

bool DirectedGraph::dfs_check_cycle_from_node(
    const int &node_idx, std::vector<bool> &visited,
    std::vector<bool> visited_in_path) {

  visited[node_idx] = true;
  visited_in_path[node_idx] = true;

  auto leaving_edges = nodes[node_idx]->get_leaving_edges();
  // traverse for adjacent nodes
  for (auto e : leaving_edges) {
    auto start_node = e->get_start_node()->get_id();
    auto end_node = e->get_end_node()->get_id();
    // when the node is not visited
    LOG(DEBUG) << "node: " << start_node <<
      "->" << end_node;
    LOG(DEBUG) << "visited: " << visited[end_node];
    if (!visited[end_node]) {
      if (dfs_check_cycle_from_node(end_node, visited,
                                    visited_in_path) == true){
        LOG(INFO) << "detected cycle at node: " << end_node;
        return true;
      }
    }
    // if the node has been previously visited
    // but it has to be visited on the same path
    else if (visited_in_path[end_node]) {
      LOG(INFO) << "detected cycle at node: " << end_node;
      return true;
    }
  }
  return false;
}

bool DirectedGraph::has_cycle() {
  auto visited = std::vector<bool>(n_nodes);
  auto visited_in_path = std::vector<bool>(n_nodes);

  // return false;
  for (int i = 0; i < n_nodes; i++) {
    if (!visited[i]) {
      if (dfs_check_cycle_from_node(i, visited, visited_in_path) == true)
        return true;
    }
  }

  return false;
}
