cmake_minimum_required(VERSION 3.10)

project(cli-table-cpp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tests)

add_executable(cli-table-cpp main.cpp Table.hpp Utils.hpp)

