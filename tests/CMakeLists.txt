cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(Cytrus-Test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable Link Time Optimization
set(CMAKE_INTERPROCEDUAL_OPTIMIZATION TRUE)

link_directories("${CMAKE_SOURCE_DIR}/../build/")

add_executable(${CMAKE_PROJECT_NAME} "${CMAKE_SOURCE_DIR}/Test.cpp")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/../include")

target_link_libraries(${CMAKE_PROJECT_NAME} Cytrus)
