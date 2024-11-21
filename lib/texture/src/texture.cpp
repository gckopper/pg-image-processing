#include <self/texture.hpp>

namespace self {

bool load_image(const char* path, cv::Mat& image) {
    constexpr int type[] = {CV_8UC1, 0, CV_8UC3, CV_8UC4};
    constexpr int code[] = {cv::COLOR_GRAY2BGR, 0, cv::COLOR_RGB2BGR, cv::COLOR_RGBA2BGRA};

    int height, width, n;
    unsigned char* data = stbi_load(path, &width, &height, &n, 0);
    if (data == nullptr) {
        LOG("Failed to load image: " << path);
        return false;
    }
    if (n == 2) {
        LOG("Can't handle images with only 2 channels");
        return false;
    }

    cv::Mat cv_image(height, width, type[n - 1], data);

    cv_image.copyTo(image);

    stbi_image_free(data);

    cv::cvtColor(image, image, code[n - 1]);

    return true;
}

void Texture::setup_texture(cv::Mat& image, uint8_t texture_index) {
    cv::Mat rgba;
    switch (image.type()) {
    case CV_8UC1:
        cv::cvtColor(image, rgba, cv::COLOR_GRAY2RGBA);
        break;
    case CV_8UC3:
        cv::cvtColor(image, rgba, cv::COLOR_BGR2RGBA);
        break;
    case CV_8UC4:
        cv::cvtColor(image, rgba, cv::COLOR_BGRA2RGBA);
        break;
    }
    this->texture_index = texture_index;
    glActiveTexture(GL_TEXTURE0 + this->texture_index);
    glCheckError();

    glGenTextures(1, &this->texture);
    glCheckError();

    this->bind();

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glCheckError();

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 rgba.cols,
                 rgba.rows,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 rgba.data);
    glCheckError();

    Texture::unbind();
}

void Texture::update_texture(cv::Mat& image) {
    cv::Mat rgba;
    switch (image.type()) {
    case CV_8UC1:
        cv::cvtColor(image, rgba, cv::COLOR_GRAY2RGBA);
        break;
    case CV_8UC3:
        cv::cvtColor(image, rgba, cv::COLOR_BGR2RGBA);
        break;
    case CV_8UC4:
        cv::cvtColor(image, rgba, cv::COLOR_BGRA2RGBA);
        break;
    }
    glActiveTexture(GL_TEXTURE0 + this->texture_index);
    glCheckError();
    this->bind();
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    rgba.cols,
                    rgba.rows,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    rgba.data);
    glCheckError();
    Texture::unbind();
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + this->texture_index);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glCheckError();
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
}
Texture::~Texture() { glDeleteTextures(1, &this->texture); }

} // namespace self
