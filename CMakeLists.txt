cmake_minimum_required(VERSION 3.13)
project(Zombiedice)

set(CMAKE_CXX_STANDARD 20)

# Testing
include(cmake/GetGTest.cmake)

add_executable(
    unit_tests # executable
    test/main.cpp # dependency
    )

target_link_libraries(unit_tests GTest)
