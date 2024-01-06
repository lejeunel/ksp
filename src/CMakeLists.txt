add_library(src
    directed_graph.cpp
    bellman_ford.cpp
    dijkstra.cpp
    ksp.cpp
    path.cpp
    node.cpp
    edge.cpp
    utils.cpp
    min_priority_queue.cpp
)

add_executable(edksp
  main.cpp
    easylogging++.cpp)
set_target_properties(edksp PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/build")
target_link_libraries(edksp src)
target_compile_definitions(edksp PUBLIC
  ELPP_DISABLE_LOGS
  ELPP_NO_LOG_TO_FILE
  ELPP_NO_DEFAULT_LOG_FILE)
