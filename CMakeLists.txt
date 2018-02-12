cmake_minimum_required(VERSION 3.5.1)

project(Options VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -g")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

include_directories(
    .
    /usr/local/opt/boost@1.60/include
)

link_directories(
    out
)

enable_testing()

add_subdirectory(lib)
add_subdirectory(tests)