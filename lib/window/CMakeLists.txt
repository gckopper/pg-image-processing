cmake_minimum_required(VERSION 3.25)

project(window)

add_shader("VERT_SHADER" "shaderSource.h.in" "main.vert" "mainVertShader.h")
add_shader("FRAG_SHADER" "shaderSource.h.in" "main.frag" "mainFragShader.h")

add_library(${PROJECT_NAME} STATIC "src/window.cpp" "include/self/window.hpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} glad glfw log shader input)
