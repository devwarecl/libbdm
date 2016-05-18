
cmake_minimum_required(VERSION 3.0)

project(libbdm)

set (CMAKE_CXX_STANDARD 14)

include_directories(src)

add_subdirectory(src/bdm)
add_subdirectory(src/bdminfo)
