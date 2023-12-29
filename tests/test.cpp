#include "../src/include/graph.h"
#include "../src/include/ksp.h"
#include "../src/include/misc.h"
#include <catch2/catch_test_macros.hpp>
#include <memory>

TEST_CASE("Should retrieve a single path",
          "[one-path]") {
  int nodes_in[1] = {0};
  int nodes_out[1] = {1};
  scalar_t weights[1] = {-1};
  int n_nodes = 2;
  int n_edges = 1;
  int source_node = 0;
  int sink_node = 1;
  int k = 1;
  auto ksp = KSP(std::make_unique<Graph>(n_nodes, n_edges, nodes_in, nodes_out,
                                         weights, source_node, sink_node),
                 source_node, sink_node);
  auto paths = ksp.run(k);

  REQUIRE(paths.size() == 1);
  REQUIRE(paths[0].get_id_at_position(0) == 0);
  REQUIRE(paths[0].get_id_at_position(1) == 1);
}
