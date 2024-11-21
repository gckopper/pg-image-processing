add_executable(main 
    main.cpp
    "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.h"
    "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.h"
    "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imconfig.h"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_draw.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui.h"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_tables.cpp"
    "${PROJECT_SOURCE_DIR}/extern/imgui/imgui_widgets.cpp"
    #"${PROJECT_SOURCE_DIR}/extern/imgui/imstb_rectpack.h"
    #"${PROJECT_SOURCE_DIR}/extern/imgui/imstb_textedit.h"
)
target_link_libraries(main PUBLIC window screen ${OpenCV_LIBS})
