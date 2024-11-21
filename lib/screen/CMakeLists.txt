cmake_minimum_required(VERSION 3.25)

project(screen)

file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}" *.hpp *.cpp)

message("${SRC}")

add_library(${PROJECT_NAME} STATIC "${SRC}")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} texture glad filter input)
