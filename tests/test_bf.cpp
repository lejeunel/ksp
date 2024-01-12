#include "../src/include/bellman_ford.h"
#include "../src/include/directed_graph.h"
#include "../src/include/path.h"
#include "../src/include/utils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Bellman-Ford should retrieve correct path from source to sink",
          "[BF]") {
  int nodes_in[4] = {0, 0, 1, 3};
  int nodes_out[4] = {1, 3, 2, 1};
  scalar_t weights[4] = {2, 5, 2, -4};
  int n_nodes = 4;
  int n_edges = 4;
  int source_node = 0;
  int sink_node = 2;
  auto graph = std::make_unique<DirectedGraph>(n_nodes, n_edges, nodes_in,
                                               nodes_out, weights);
  auto res = bellman_ford(*graph, source_node);
  REQUIRE(res.has_value() == true);

  auto path = Utils::make_shortest_path(*graph, source_node, sink_node).value();
  auto expected = Path(std::vector<int>{0, 3, 1, 2}, 3);

  REQUIRE(path == expected);
}
