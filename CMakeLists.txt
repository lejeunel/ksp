cmake_minimum_required(VERSION 3.10)

project(ksp)

set(SOURCES
    src/graph.cpp
    src/ksp.cpp
    src/path.cpp
    src/node.cpp
    src/edge.cpp
    src/easylogging++.cpp
)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(test tests/test.cpp ${SOURCES})
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
