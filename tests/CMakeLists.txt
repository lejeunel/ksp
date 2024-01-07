Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

# test suite
add_executable(test
  test.cpp
  test_cycle.cpp
  test_bf.cpp
  test_djk.cpp
  test_ksp.cpp
    ../src/easylogging++.cpp
)

# target_compile_definitions(test PUBLIC
#   ELPP_DISABLE_LOGS
#   ELPP_NO_LOG_TO_FILE
#   ELPP_NO_DEFAULT_LOG_FILE)
target_link_libraries(test PUBLIC Catch2::Catch2WithMain src)
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/build")
