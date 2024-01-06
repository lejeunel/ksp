#include "../src/include/dijkstra.h"
#include "../src/include/directed_graph.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Dijkstra should retrieve correct path from source to sink", "djk") {
  int nodes_in[7] = {0, 0, 1, 1, 2, 4, 3};
  int nodes_out[7] = {1, 2, 2, 3, 4, 3, 5};
  scalar_t weights[7] = {4, 2, 5, 10, 3, 4, 11};
  int n_nodes = 6;
  int n_edges = 7;
  int source_node = 0;
  int sink_node = 5;
  auto graph = std::make_shared<DirectedGraph>(n_nodes, n_edges, nodes_in,
                                               nodes_out, weights);
  auto djk = Dijkstra(graph, source_node);
  auto nodes = djk.run().value();
  auto path = nodes[sink_node]->make_path_from_root().value();

  REQUIRE(path.is_equal(std::vector<int>{0, 2, 4, 3, 5}));
}
