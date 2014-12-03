project(DFS)
cmake_minimum_required(VERSION 2.8)
include_directories(${DFS_SOURCE_DIR})


#aux_source_directory(. SRC_LIST)
add_executable(main main.cpp Graph.cpp Graph.h
 Node.cpp Node.h Edge.h Edge.cpp
 gtest-all.cc gtest.h gtest_main.cc)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -pedantic")


target_link_libraries(main -lpthread)
