set(PACKAGE_NAME "libwebp")
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/${PACKAGE_NAME}/CMakeLists.txt")
    find_package(Git QUIET)

    if(GIT_FOUND)
        if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
            execute_process(COMMAND "${GIT_EXECUTABLE} submodule update --init extern/${PACKAGE_NAME}"
                            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                            RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init extern/${PACKAGE_NAME} failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        else()
            message(FATAL_ERROR "This is not a git repository and the extern/${PACKAGE_NAME} directory does not contain a CMakeLists.txt. Since this is not a repository we can't sync the submodules. To fix this download a zip archive from the official ${PACKAGE_NAME} github and extract it inside the extern/${PACKAGE_NAME} folder. The file extern/${PACKAGE_NAME}/CMakeLists.txt should exist.")
        endif()
    else()
        message(FATAL_ERROR "Git was not found and the extern/${PACKAGE_NAME} directory does not contain a CMakeLists.txt. The directory is a git submodule and the files should be downloaded with git, however, if necessary, download a zip archive from the official ${PACKAGE_NAME} github and extract it inside the extern/${PACKAGE_NAME} folder. The file extern/${PACKAGE_NAME}/CMakeLists.txt should exist. Or simply turn the tests off by setting PACKAGE_TESTS=OFF")
    endif()
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/${PACKAGE_NAME} ${CMAKE_BINARY_DIR}/${PACKAGE_NAME})

set(WEBP_BUILD_ANIM_UTILS OFF)
set(WEBP_BUILD_CWEBP OFF)
set(WEBP_BUILD_DWEBP OFF)
set(WEBP_BUILD_GIF2WEBP OFF)
set(WEBP_BUILD_IMG2WEBP OFF)
set(WEBP_BUILD_VWEBP OFF)
set(WEBP_BUILD_WEBPINFO OFF)
set(WEBP_BUILD_LIBWEBPMUX OFF)
set(WEBP_BUILD_WEBPMUX OFF)
set(WEBP_BUILD_EXTRAS OFF)

set(WEBP_LINK_STATIC ON)
