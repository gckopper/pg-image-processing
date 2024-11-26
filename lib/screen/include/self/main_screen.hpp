#pragma once

#include <chrono>
#include <format>
#include <opencv2/opencv.hpp>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <glad/gl.h>

#include <self/filter.hpp>
#include <self/input.hpp>
#include <self/screen.hpp>
#include <self/texture.hpp>

namespace self {

constexpr std::array<std::string_view, 5> STICKER_PATHS = {
    "./stickers/bigode.png",
    "./stickers/chapeu.png",
    "./stickers/pin.png",
    "./stickers/bone.png",
    "./stickers/estrela.png"};

constexpr std::array<std::string_view, 5> STICKER_NAMES = {
    "Bigode", "Chapeu", "Red circle", "Boné", "Estrela"};

struct Transformation {
    float x = 10.f;
    float y = 10.f;
    float rot = 0.f;
    float scalex = 1.f;
    float scaley = 1.f;
    int32_t sticker;
};

struct UI {
    bool save = false, edge_detect = false, gaussian = false, box_blur = false,
         fry = false, bitwise_not = false, canny = false, median_blur = false,
         grayscale = false, wow = false, sharpen = false, dog = false;
    int gaussian_ksize = 13, box_blur_ksize = 13, median_blur_ksize = 13,
        dog_ksize = 5, dog_std = 1, sharpen_strengh = 1;
    float rotation = 0.0f, scale = 1.0f;
};

constexpr int MAX_STICKERS = 128;

class MainScreen : Screen {
  private:
    cv::VideoCapture cap;
    GLuint vao;
    GLuint vbo;
    void setup_buffers();
    void update_frame();
    int width, height;
    char* image_path = nullptr;
    UI ui;
    std::array<Texture, 6> textures = {};
    cv::Mat frame = {};
    std::vector<Transformation> transformations;

  public:
    void render() override;
    void render_ui() override;
    bool logic() override;
    void update_ui() override;
    bool init(int argc, char** argv) override;
    void quit() override;
};

} // namespace self
