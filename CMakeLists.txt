cmake_minimum_required(VERSION 3.15)
project(Zombiedice)

set(CMAKE_CXX_STANDARD 20)

# Testing
include(cmake/GetGTest.cmake)

add_executable(unit_tests)
target_link_libraries(unit_tests GTest)
