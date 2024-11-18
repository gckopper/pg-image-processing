#pragma once

#include <chrono>
#include <format>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <webp/encode.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <glad/gl.h>

#include <self/filter.hpp>
#include <self/screen.hpp>
#include <self/texture.hpp>

namespace self {

class MainScreen : Screen {
  private:
    Texture texture;
    cv::VideoCapture cap;
    GLuint vao;
    void setup_buffers();
    void update_frame();
    cv::Mat frame;
    bool edge_detect = false, gaussian = false, box_blur = false, fry = false;

  public:
    void render() override;
    void logic() override;
    bool init() override;
    void quit() override;
};

} // namespace self
