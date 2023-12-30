#include "../src/include/directed_graph.h"
#include <catch2/catch_test_macros.hpp>

#include "../src/include/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

TEST_CASE("Should detect cycle", "[cycle]") {
  int nodes_in[3] = {0, 1, 2};
  int nodes_out[3] = {1, 2, 0};
  scalar_t weights[2] = {0};
  int n_nodes = 3;
  int n_edges = 3;

  DirectedGraph graph(n_nodes, n_edges, nodes_in, nodes_out, weights);
  REQUIRE(graph.has_cycle() == true);
}

TEST_CASE("Should detect no cycle", "[cycle]") {
  int nodes_in[4] = {0, 1, 0, 3};
  int nodes_out[4] = {1, 2, 3, 2};
  scalar_t weights[4] = {0};
  int n_nodes = 4;
  int n_edges = 4;

  DirectedGraph graph(n_nodes, n_edges, nodes_in, nodes_out, weights);

  REQUIRE(graph.has_cycle() == false);
}
