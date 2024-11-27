cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

option(CROSS_COMPILE "Cross compile to Windows" OFF)
if(CROSS_COMPILE)
    include(CrossCompile)
endif()

project(grauB)

include(SetDefaultBuild)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Og -g -pedantic")
endif()

option(PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
    enable_testing()
    include(AddGoogleTest)
    add_subdirectory(tests)
endif()

include(TemplateShader)

include_directories("${CMAKE_BINARY_DIR}/generated_headers/")

include(AddGlad)
include(AddGLFW)
include(AddSTB)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(extern/imgui/)

add_subdirectory("lib")
add_subdirectory("src")
