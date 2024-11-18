function(add_shader SHADER_NAME TEMPLATE SHADER GENERATED_HEADER) 
    message("${CMAKE_SOURCE_DIR}/shaders/${SHADER}")
    add_custom_target( "${SHADER_NAME}" ALL
    COMMAND ${CMAKE_COMMAND} 
        -DSHADER_NAME=${SHADER_NAME} 
        -DINPUT="${CMAKE_SOURCE_DIR}/shaders/${SHADER}"
        -DTEMPLATE="${CMAKE_SOURCE_DIR}/templates/${TEMPLATE}"
        -DOUTPUT="${CMAKE_BINARY_DIR}/generated_headers/${GENERATED_HEADER}"
        -P "${CMAKE_SOURCE_DIR}/cmake/GenerateFromTemplate.cmake" 
    DEPENDS "${CMAKE_SOURCE_DIR}/shaders/${SHADER}" "${CMAKE_SOURCE_DIR}/templates/${TEMPLATE}"
    )
endfunction()

# 
 
