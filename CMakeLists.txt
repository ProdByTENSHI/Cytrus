cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(Cytrus VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable Link Time Optimization
set(CMAKE_INTERPROCEDUAL_OPTIMIZATION TRUE)

add_library(Cytrus STATIC "${CMAKE_SOURCE_DIR}/lib/Main.cpp")

add_subdirectory("${CMAKE_SOURCE_DIR}/lib")

message("Using Compiler: " ${CMAKE_CXX_COMPILER_ID})
