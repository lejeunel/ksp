cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ksp)

set(SOURCES
    src/directed_graph.cpp
    src/bellman_ford.cpp
    src/dijkstra.cpp
    src/ksp.cpp
    src/path.cpp
    src/node.cpp
    src/edge.cpp
    src/utils.cpp
    src/min_priority_queue.cpp
    src/easylogging++.cpp
)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# test suite
add_executable(test
  tests/test.cpp
  tests/test_cycle.cpp
  tests/test_bf.cpp
  tests/test_djk.cpp
  tests/test_ksp.cpp
  ${SOURCES})
target_compile_definitions(test PUBLIC ELPP_DISABLE_LOGS)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
