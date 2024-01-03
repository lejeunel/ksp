#include "../src/include/directed_graph.h"
#include <catch2/catch_test_macros.hpp>

#include "../src/include/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

TEST_CASE("Should detect cycle", "[cycle]") {
  int nodes_in[9] = {0, 1, 2, 6, 4, 7, 7, 9, 8};
  int nodes_out[9] = {1, 2, 3, 4, 5, 1, 8, 7, 9};
  scalar_t weights[9] = {0};
  int n_nodes = 10;
  int n_edges = 9;

  DirectedGraph graph(n_nodes, n_edges, nodes_in, nodes_out, weights);
  REQUIRE(graph.has_cycle() == true);
}

TEST_CASE("Should detect no cycle", "[cycle]") {
  int nodes_in[9] = {0, 1, 2, 6, 4, 7, 7, 8};
  int nodes_out[9] = {1, 2, 3, 4, 5, 1, 8, 9};
  scalar_t weights[8] = {0};
  int n_nodes = 10;
  int n_edges = 8;

  DirectedGraph graph(n_nodes, n_edges, nodes_in, nodes_out, weights);

  REQUIRE(graph.has_cycle() == false);
}
