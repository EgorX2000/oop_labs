cmake_minimum_required(VERSION 3.10)

project("lab_7")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(googletest)

include_directories(
    src/Npc
    src/Observer
    src/NpcManager
    src/Factory
    src/Visitor
)

set(SOURCES
    main.cpp
    src/Npc/Npc.cpp
    src/Observer/Observer.cpp
    src/NpcManager/NpcManager.cpp
    src/Factory/Factory.cpp
    src/Visitor/Visitor.cpp
)

add_library(Lib STATIC ${SOURCES})

add_executable(main main.cpp)

target_link_libraries(main Lib)

enable_testing()

set(TEST_SOURCES
    tests.cc
)

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests gtest gtest_main Lib)
