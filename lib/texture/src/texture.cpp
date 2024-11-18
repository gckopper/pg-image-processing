#include <self/texture.hpp>

namespace self {
void Texture::setup_texture(cv::Mat& image) {
    glActiveTexture(GL_TEXTURE0);
    glCheckError();

    glGenTextures(1, &this->texture);
    glCheckError();

    this->bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB8,
                 image.cols,
                 image.rows,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image.data);
    glCheckError();

    Texture::unbind();
}

void Texture::update_texture(cv::Mat& image) {
    this->bind();
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    image.cols,
                    image.rows,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    image.data);
    glCheckError();
    Texture::unbind();
}

void Texture::bind() { 
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glCheckError();
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0); 
    glCheckError();
}
Texture::~Texture() {
    glDeleteTextures(1, &this->texture);
}

} // namespace self
