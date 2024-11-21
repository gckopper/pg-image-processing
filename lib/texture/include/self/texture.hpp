#pragma once

#include <cstdint>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <stb/stb_image.h>

#include <glad/gl.h>

#include <self/log.hpp>

namespace self {

bool load_image(const char* path, cv::Mat& image);

class Texture {
  private:
    GLuint texture;
    uint8_t texture_index = 0;

  public:
    void setup_texture(cv::Mat& image, uint8_t texture_index);

    void update_texture(cv::Mat& image);

    void bind();
    static void unbind();
    ~Texture();
};

} // namespace self
