cmake_minimum_required(VERSION 3.13)
project(Zombiedice)

set(CMAKE_CXX_STANDARD 20)

include(cmake/GetGTest.cmake)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    )

add_library(
    example
    src/example.cpp
    )

add_executable(
    unit_tests # executable
    tests/main.cpp # dependency
    tests/example_add.cpp # dependency
)

add_dependencies(unit_tests GTest)

target_link_libraries(
    unit_tests
    GTest
    example
    pthread
    )

enable_testing()

# add_subdirectory(src)
# add_subdirectory(tests)
