cmake_minimum_required(VERSION 3.25)

project(filter)

add_library(${PROJECT_NAME} STATIC "include/self/filter.hpp" "src/filter.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME})
