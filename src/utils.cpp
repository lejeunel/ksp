#include "include/utils.h"
#include "include/common.h"
#include "include/easylogging++.h"
#include "include/edge.h"
#include "include/misc.h"

std::vector<int> Utils::make_indices(const int &size) {
  std::vector<int> indices;
  indices.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    indices.push_back(i);
  }

  return indices;
}

std::expected<std::vector<int>, std::string>
Utils::topological_sort(std::shared_ptr<DirectedGraph> const &graph) {

  auto n_nodes = graph->n_nodes();

  // compute in-degree of each node
  std::vector<int> indegree(n_nodes, 0);
  int tgt_id;
  for (int n = 0; n < n_nodes; n++) {
    for (auto e : (*graph)[n]->out_edges) {
      tgt_id = e->target_node->get_id();
      indegree[tgt_id]++;
    }
  }

  // Initially insert elements who has
  // indegree 0
  std::vector<int> ans;
  std::queue<int> qrr;
  for (int n = 0; n < n_nodes; n++) {

    if (indegree[n] == 0) {
      qrr.push(n);
    }
  }

  int count = 0;
  while (!qrr.empty()) {
    // push those elements in queue which
    // poses 0 indegree
    int node = qrr.front();

    qrr.pop();
    ans.push_back(node);
    for (auto e : (*graph)[node]->out_edges) {
      tgt_id = e->target_node->get_id();
      indegree[tgt_id]--;
      if (indegree[tgt_id] == 0) {
        qrr.push(tgt_id);
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
