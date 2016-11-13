cmake_minimum_required(VERSION 3.6)
project(BST_HW)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp binary_tree.h binary_tree.cpp)
add_executable(BST_HW ${SOURCE_FILES})