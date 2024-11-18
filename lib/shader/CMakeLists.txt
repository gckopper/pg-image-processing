cmake_minimum_required(VERSION 3.25)

project(shader)

add_library(${PROJECT_NAME} STATIC "include/self/shader.hpp" "src/shader.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} glad log)
