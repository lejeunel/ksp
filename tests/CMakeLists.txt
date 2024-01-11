include(FetchContent)
fetchcontent_declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

fetchcontent_makeavailable(Catch2)

# test suite
add_executable(tests
  main.cpp
  test.cpp
  test_cycle.cpp
  test_bf.cpp
  test_djk.cpp
  test_ksp.cpp
../src/easylogging++.cpp
../src/logger.cpp
)

target_link_libraries(tests PUBLIC Catch2::Catch2 ksp)
