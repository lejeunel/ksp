#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#include "common.h"
#include "directed_graph.h"
#include "easylogging++.h"
#include "min_priority_queue.h"
#include "utils.h"
#include <expected>

std::expected<int, std::string> dijkstra(DirectedGraph &a_graph,
                                         const int &a_source);

#endif // DIJKSTRA_H_
