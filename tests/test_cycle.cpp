#include "../src/include/bellman_ford.h"
#include "../src/include/directed_graph.h"
#include "../src/include/ksp.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Graph with cycle should return error", "[cycle]") {
  int nodes_in[5] = {0, 0, 1, 3, 2};
  int nodes_out[5] = {1, 3, 2, 1, 3};
  scalar_t weights[5] = {2, 5, 2, -4, 0};
  int n_nodes = 4;
  int n_edges = 5;
  int source_node = 0;
  auto graph = std::make_unique<DirectedGraph>(n_nodes, n_edges, nodes_in,
                                               nodes_out, weights);
  auto res = bellman_ford(*graph, source_node);

  REQUIRE(res.has_value() == false);
}
