#include "../src/include/directed_graph.h"
#include "../src/include/ksp.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("KSP should retrieve correct set of paths from source to sink",
          "[KSP]") {
  int nodes_in[10] = {0, 1, 2, 0, 3, 1, 4, 3, 0, 6};
  int nodes_out[10] = {1, 2, 5, 3, 2, 4, 5, 5, 6, 5};
  scalar_t weights[10] = {1, 1, 1, 4, 1, 3, 1, 8, 15, 1};
  int n_nodes = 7;
  int n_edges = 10;
  int source_node = 0;
  int sink_node = 5;

  auto graph = std::make_shared<DirectedGraph>(n_nodes, n_edges, nodes_in,
                                               nodes_out, weights);
  auto ksp = KSP(graph, source_node, sink_node);

  SECTION("k=1") {
    auto path = ksp.run(1).value()[0];

    REQUIRE(path->is_equal(std::vector<int>{0, 1, 2, 5}));
    REQUIRE(path->get_length() == 3);
  }

  SECTION("k=2") {
    auto paths = ksp.run(2).value();

    REQUIRE(paths[0]->get_length() == 5);
    REQUIRE(paths[1]->get_length() == 6);
  }
  SECTION("k=3") {
    auto paths = ksp.run(3).value();
    REQUIRE(paths[2]->is_equal(std::vector<int>{0, 6, 5}));
  }
}
