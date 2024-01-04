#include "include/utils.h"
#include "include/common.h"
#include "include/edge.h"
#include "include/misc.h"

std::vector<int> make_indices(const int &size) {
  std::vector<int> indices;
  indices.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    indices.push_back(i);
  }

  return indices;
}

std::expected<std::vector<int>, std::string>
topological_sort(std::unique_ptr<DirectedGraph> const &graph) {

  auto n_nodes = graph->n_nodes();

  std::vector<int> indegree(n_nodes, 0);
  int tgt_id;
  // Code for make indegree
  for (int n = 0; n < n_nodes; n++) {
    for (auto e : graph->get_node(n)->get_leaving_edges()) {
      tgt_id = e->get_target_node()->get_id();
      indegree[tgt_id]++;
    }
  }

  std::vector<int> ans;
  std::queue<int> qrr;
  // Initially insert elements who has
  // indegree 0
  for (int n = 0; n < n_nodes; n++) {

    if (indegree[n] == 0) {
      qrr.push(n);
    }
  }

  while (!qrr.empty()) {
    // push those elements in queue which
    // poses 0 indegree
    int node = qrr.front();

    qrr.pop();
    ans.push_back(node);
    for (auto e : graph->get_node(node)->get_leaving_edges()) {
      tgt_id = e->get_target_node()->get_id();
      indegree[tgt_id]--;
      if (indegree[tgt_id] == 0) {
        qrr.push(tgt_id);
      }
    }
  }
  return ans;
}
