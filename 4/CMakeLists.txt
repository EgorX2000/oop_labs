cmake_minimum_required(VERSION 3.10)

project("lab_4")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(googletest)

add_library(figures figures/Figures.cpp)

add_executable(main main.cpp)
target_link_libraries(main figures)

add_executable(tests tests/tests.cc)
target_link_libraries(tests gtest_main figures)