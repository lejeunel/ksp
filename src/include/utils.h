#ifndef UTILS_H_
#define UTILS_H_

#include "directed_graph.h"
#include <expected>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace Utils {

std::expected<std::vector<int>, std::string>
topological_sort(std::shared_ptr<DirectedGraph> const &graph);

std::vector<int> make_indices(const int &size);
NodePtr deep_copy_node(NodePtr const &);

} // namespace Utils
#endif // UTILS_H_
