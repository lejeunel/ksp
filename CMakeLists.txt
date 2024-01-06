cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ksp)

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
