#ifndef BELLMAN_FORD_H_
#define BELLMAN_FORD_H_

#include "common.h"
#include "directed_graph.h"
#include "easylogging++.h"
#include "edge.h"
#include "node.h"
#include <expected>

std::expected<int, std::string> bellman_ford(DirectedGraph &graph,
                                             const int &source);
std::expected<std::vector<int>, std::string>
sort_nodes(const DirectedGraph &graph);

#endif // BELLMAN_FORD_H_
