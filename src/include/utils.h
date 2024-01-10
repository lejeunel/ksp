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
topological_sort(const DirectedGraph &graph);

std::vector<int> make_indices(const int &size);

} // namespace Utils
#endif // UTILS_H_
