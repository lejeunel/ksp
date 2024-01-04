#ifndef BELLMAN_FORD_H_
#define BELLMAN_FORD_H_

#include "common.h"
#include "directed_graph.h"
#include "tree_node.h"
#include <expected>

class BellmanFord {

public:
  BellmanFord(std::unique_ptr<DirectedGraph> const &graph, const int &source,
              bool const &a_do_topological_sort);
  std::expected<std::vector<std::shared_ptr<TreeNode>>, std::string>
  run(std::unique_ptr<DirectedGraph> const &, const int &source);
  Path generate_path_to_root(const int &start);

private:
  std::expected<std::vector<int>, std::string>
  sort_nodes(std::unique_ptr<DirectedGraph> const &);
  std::vector<std::shared_ptr<TreeNode>> tree_nodes;

  bool do_topological_sort = false;
};
#endif // BELLMAN_FORD_H_
