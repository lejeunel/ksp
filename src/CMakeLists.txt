add_library(ksp
    directed_graph.cpp
    bellman_ford.cpp
    dijkstra.cpp
    path.cpp
    node.cpp
    edge.cpp
    min_priority_queue.cpp
    logger.cpp
    easylogging++.cpp
    ksp.cpp
)

add_executable(edksp
  main.cpp)


target_link_libraries(edksp ksp)
