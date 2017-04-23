cmake_minimum_required (VERSION 3.0)
project (DummyProject)

# We heavily use C++11, C++11 support is required
set (CMAKE_CXX_STANDARD 11)

add_subdirectory("${CMAKE_SOURCE_DIR}/externals/pybind11")
add_definitions(-DPYBIND11)
pybind11_add_module(dummy "${CMAKE_SOURCE_DIR}/main.cpp")
