cmake_minimum_required(VERSION 3.10)

project("lab_3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(googletest)

add_library(task task/task.cpp task/task.h)

add_executable(main main.cpp)
target_link_libraries(main task)

add_executable(tests tests.cpp)
target_link_libraries(tests gtest_main task)