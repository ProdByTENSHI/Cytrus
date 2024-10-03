file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/lib/*.cpp")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${src})
