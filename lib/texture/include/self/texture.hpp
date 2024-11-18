#pragma once

#include <opencv2/core/mat.hpp>

#include <glad/gl.h>

#include <self/log.hpp>

namespace self {

class Texture {
  private:
    GLuint texture;

  public:
    void setup_texture(cv::Mat& image);
    void update_texture(cv::Mat& image);
    void bind();
    static void unbind();
    ~Texture();
};

} // namespace self
