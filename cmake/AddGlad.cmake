if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/glad/src/gl.c")
    message(FATAL_ERROR "Glad not found!")
endif()

# Path to glad directory
set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/extern/glad/")

include_directories(${GLAD_SOURCES_DIR}/include)
file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR} *.c ${GLAD_SOURCES_DIR}/src/gl.c)
add_library(glad STATIC ${GLAD_SOURCES_DIR}/src/gl.c)
