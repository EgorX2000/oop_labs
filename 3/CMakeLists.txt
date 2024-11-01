cmake_minimum_required(VERSION 3.10)

project("lab_3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(googletest)

add_library(figures figures/Figures.h figures/Figures.cpp figures/Octagon.cpp figures/Triangle.cpp figures/Square.cpp)

add_executable(main main.cpp)
target_link_libraries(main figures)

add_executable(tests tests/tests.cc)
target_link_libraries(tests gtest_main figures)