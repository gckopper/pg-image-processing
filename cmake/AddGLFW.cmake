if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/glfw/CMakeLists.txt")
    find_package(Git QUIET)

    if(GIT_FOUND)
        if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init extern/glfw
                            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init extern/glfw failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        else()
            message(FATAL_ERROR "This is not a git repository and the extern/glfw directory does not contain a CMakeLists.txt. Since this is not a repository we can't sync the submodules. To fix this download a zip archive from the official glfw github and extract it inside the extern/glfw folder. The file extern/glfw/CMakeLists.txt should exist.")
        endif()
    else()
        message(FATAL_ERROR "Git was not found and the extern/glfw directory does not contain a CMakeLists.txt. The directory is a git submodule and the files should be downloaded with git, however, if necessary, download a zip archive from the official glfw github and extract it inside the extern/glfw folder. The file extern/glfw/CMakeLists.txt should exist.")
    endif()
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/glfw ${CMAKE_BINARY_DIR}/glfw)
