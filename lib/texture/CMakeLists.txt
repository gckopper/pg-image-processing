cmake_minimum_required(VERSION 3.25)

project(texture)

add_library(${PROJECT_NAME} STATIC "src/texture.cpp" "include/self/texture.hpp")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} glad log stb)
