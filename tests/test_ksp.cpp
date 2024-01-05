#include "../src/include/directed_graph.h"
#include "../src/include/ksp.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("KSP should retrieve correct set of paths from source to sink",
          "ksp") {
  int nodes_in[12] = {0, 1, 2, 3, 0, 4, 5, 4, 1, 5, 0, 6};
  int nodes_out[12] = {1, 2, 3, 7, 4, 5, 7, 1, 5, 3, 6, 7};
  scalar_t weights[12] = {1, 1, 1, 1, 1, 3, 5, 1, 1, 2, 7, 2};
  int n_nodes = 8;
  int n_edges = 12;
  int source_node = 0;
  int sink_node = 7;

  auto graph = std::make_shared<DirectedGraph>(n_nodes, n_edges, nodes_in,
                                               nodes_out, weights);
  auto ksp = KSP(graph, source_node, sink_node);

  SECTION("k=1") {
    auto path = ksp.run(1).value()[0];

    REQUIRE(path == std::vector<int>{0, 1, 2, 3, 7});
    REQUIRE(path.get_length() == 4);
  }

  SECTION("k=2") {
    auto paths = ksp.run(2).value();

    REQUIRE(paths[0] == std::vector<int>{0, 1, 2, 3, 7});
    REQUIRE(paths[0].get_length() == 4);
    REQUIRE(paths[1] == std::vector<int>{0, 4, 1, 5, 7});
    REQUIRE(paths[1].get_length() == 8);
  }

  SECTION("k=3") {
    auto paths = ksp.run(3).value();

    REQUIRE(paths[0] == std::vector<int>{0, 1, 2, 3, 7});
    REQUIRE(paths[1] == std::vector<int>{0, 4, 1, 5, 7});
    REQUIRE(paths[2] == std::vector<int>{0, 6, 7});
  }
}
