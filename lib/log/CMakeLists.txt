cmake_minimum_required(VERSION 3.25)

project(log)

add_library(${PROJECT_NAME} STATIC "src/log.cpp" "include/self/log.hpp")

target_link_libraries(${PROJECT_NAME} glad)

target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG=1)

target_include_directories(${PROJECT_NAME} PUBLIC "include")
