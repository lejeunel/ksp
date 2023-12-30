#include "../src/include/graph.h"
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
        KSP(std::make_unique<Graph>(n_nodes, n_edges, nodes_in, nodes_out,
                                    weights),
            source_node, sink_node);
    auto paths = ksp.run(k);

    REQUIRE(paths.size() == 1);
    REQUIRE(paths[0][0]->get_id() == 0);
    REQUIRE(paths[0][1]->get_id() == 1);
  }

  SECTION("""Should detect that source has only leaving\
 edges and sink only incoming edges""",
 "[validation]") {
    auto invalid_ksp =
        KSP(std::make_unique<Graph>(n_nodes, n_edges, nodes_in, nodes_out,
                                    weights),
            sink_node, source_node);
    bool is_valid = invalid_ksp.validate_source_sink();
    REQUIRE(is_valid == false);

    auto valid_ksp =
        KSP(std::make_unique<Graph>(n_nodes, n_edges, nodes_in, nodes_out,
                                    weights),
            source_node, sink_node);

    is_valid = valid_ksp.validate_source_sink();
    REQUIRE(is_valid == true);

  }
}
