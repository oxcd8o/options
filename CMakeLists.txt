cmake_minimum_required(VERSION 3.5.1)

project(Options VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++14 -g")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

add_library(options lib/src/options.cpp lib/src/impl.cpp)
target_include_directories(options PRIVATE . /usr/local/opt/boost@1.60/include)

add_executable(options_test tests/options.cpp)
target_include_directories(options_test PRIVATE . /usr/local/opt/boost@1.60/include)
target_link_libraries(options_test options)