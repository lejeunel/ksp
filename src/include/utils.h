#ifndef UTILS_H_
#define UTILS_H_

#include "directed_graph.h"
#include <expected>
#include <memory>
#include <queue>
#include <string>
#include <vector>

std::expected<std::vector<int>, std::string>
topological_sort(std::unique_ptr<DirectedGraph> const &graph);

std::vector<int> make_indices(const int &size);

#endif // UTILS_H_
