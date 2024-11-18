#pragma once

#include <cstdint>
#include <cstdlib>
#include <string_view>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <self/log.hpp>

namespace self {

class Window {
  private:
    GLFWwindow* window;

  public:
    void setup(const std::string_view title,
               const int32_t height,
               const int32_t width);
    void change_title(std::string_view title);
    void get_input();
    void request_frame();
    void swap_buffers();
    void close();
    bool should_close();
};

} // namespace self
