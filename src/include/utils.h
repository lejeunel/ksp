#ifndef UTILS_H_
#define UTILS_H_

#include "directed_graph.h"
#include "easylogging++.h"
#include "edge.h"
#include "min_priority_queue.h"
#include "node.h"
#include "path.h"
#include <expected>
#include <memory>
#include <queue>
#include <string>
#include <vector>

namespace Utils {

std::expected<std::vector<int>, std::string>
topological_sort(const DirectedGraph &graph);

void initialize_distances_from_source(DirectedGraph &graph,
                                      const int &source_id);

void clip_all_edges(DirectedGraph &graph, const scalar_t &min);
void positivize_edges(DirectedGraph &graph);

void set_edges_occupied_on_path(DirectedGraph &graph, const Path &p,
                                const bool &val);
void set_all_edges_occupied(DirectedGraph &graph, const bool &val);

// _unless_ edge is interlaced, invert it
void invert_edges_on_path(DirectedGraph &graph, const Path &p);

// a new shortest path that passes through an "occupied" edge
// must be detected. We call such edge "interlaced", and set
// "interlaced" flag to true.
void set_edges_interlaced_on_path(DirectedGraph &graph, const Path &p);

void reset_all_edges(DirectedGraph &graph);

std::expected<Path, std::string> make_shortest_path(DirectedGraph &graph,
                                                    const int &start_node_id,
                                                    const int &end_node_id);

} // namespace Utils
#endif // UTILS_H_
