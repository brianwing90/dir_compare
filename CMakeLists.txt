cmake_minimum_required(VERSION 3.22)
project(dir-compare)

set(CMAKE_CXX_STANDARD 17)
include(CTest)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
