cmake_minimum_required(VERSION 3.19)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)

include_directories(..)
add_executable(AdventOfCode main.cpp)
target_compile_options(AdventOfCode PRIVATE -Wall -Wextra -Wpedantic -Werror -O3)
