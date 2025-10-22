find_package(Catch2 REQUIRED)

# test suite
add_executable(test
  main.cpp
  test.cpp
  test_cycle.cpp
  test_bf.cpp
  test_djk.cpp
  test_ksp.cpp
../src/easylogging++.cpp
../src/logger.cpp
)

target_link_libraries(test PUBLIC Catch2::Catch2 ksp)
