add_library(src
    directed_graph.cpp
    sp_common.cpp
    bellman_ford.cpp
    dijkstra.cpp
    path.cpp
    node.cpp
    edge.cpp
    utils.cpp
    min_priority_queue.cpp
    logger.cpp
    easylogging++.cpp
    ksp.cpp
)

add_executable(edksp
  main.cpp)


target_link_libraries(edksp src)
set_target_properties(edksp PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/build")
