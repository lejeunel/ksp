#ifndef UTILS_H_
#define UTILS_H_

#include "directed_graph.h"
#include "tree_node.h"
#include <expected>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace Utils {

std::expected<std::vector<int>, std::string>
topological_sort(std::shared_ptr<DirectedGraph> const &graph);

std::vector<int> make_indices(const int &size);

std::vector<SPTreeNodePtr>
init_tree_nodes(std::shared_ptr<DirectedGraph> const &a_graph,
                const int &source);
} // namespace Utils
#endif // UTILS_H_
