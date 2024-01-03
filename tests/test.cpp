#include "../src/include/directed_graph.h"
#include "../src/include/ksp.h"
#include "../src/include/misc.h"
#include <catch2/catch_test_macros.hpp>
#include <memory>

TEST_CASE("Create graph and perform basic validation", "[one-path]") {
  int nodes_in[1] = {0};
  int nodes_out[1] = {1};
  scalar_t weights[1] = {-1};
  int n_nodes = 2;
  int n_edges = 1;
  int source_node = 0;
  int sink_node = 1;
  int k = 1;

  SECTION("should retrieve a single path from source to sink") {
    auto ksp =
        KSP(std::make_unique<DirectedGraph>(n_nodes, n_edges, nodes_in, nodes_out,
                                    weights),
            source_node, sink_node);
    auto result = ksp.run(k);
    auto paths = result.value();

    REQUIRE(paths.size() == 1);
    REQUIRE(paths[0][0]->get_id() == 0);
    REQUIRE(paths[0][1]->get_id() == 1);
  }

  SECTION("""Should detect that source has no leaving edges""",
 "[validation]") {
    auto ksp =
        KSP(std::make_unique<DirectedGraph>(n_nodes, n_edges, nodes_in, nodes_out,
                                    weights),
            sink_node, source_node);
    auto result = ksp.run(1);

    REQUIRE(result.has_value() == false);
  }

  SECTION("""Should detect that source has leaving edges""",
 "[validation]") {
    auto ksp =
        KSP(std::make_unique<DirectedGraph>(n_nodes, n_edges, nodes_in, nodes_out,
                                    weights),
            source_node, sink_node);

    auto result = ksp.run(1);
    REQUIRE(result.has_value() == true);

  }
}
