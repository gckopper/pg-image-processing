#include <self/main_screen.hpp>

namespace self {

void MainScreen::setup_buffers() {
    // clang-format off
    GLfloat vertices[] = {
        // x   y     z
        -1.0, -1.0, 0.0, 
         1.0, -1.0, 0.0, 
        -1.0,  1.0, 0.0, 
         1.0,  1.0, 0.0, 
    };
    // clang-format on

    GLuint VBO;

    glGenBuffers(1, &VBO);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glCheckError();

    glGenVertexArrays(1, &this->vao);
    glCheckError();

    glBindVertexArray(this->vao);
    glCheckError();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glCheckError();
    glEnableVertexAttribArray(0);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();

    glBindVertexArray(0);
    glCheckError();
}

void MainScreen::update_frame() {
    this->cap.read(this->frame);
    switch (this->frame.type()) {
    case CV_8UC1:
        cv::cvtColor(this->frame, this->frame, cv::COLOR_GRAY2RGB);
        break;
    case CV_8UC3:
        cv::cvtColor(this->frame, this->frame, cv::COLOR_BGR2RGB);
        break;
    case CV_8UC4:
        cv::cvtColor(this->frame, this->frame, cv::COLOR_BGRA2RGB);
        break;
    }
}

void MainScreen::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // cor de fundo
    glCheckError();
    glClear(GL_COLOR_BUFFER_BIT);
    glCheckError();

    glBindVertexArray(this->vao); // Conectando ao buffer de geometria
    glCheckError();

    this->texture.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glCheckError();
    self::Texture::unbind();

    glBindVertexArray(0);
    glCheckError();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainScreen::logic() {
    ImGui::Begin("Control");

    ImGui::Checkbox("Edge detection", &edge_detect);
    ImGui::Checkbox("Fry", &fry);
    ImGui::Checkbox("Gaussian blur", &gaussian);
    ImGui::Checkbox("Box blur", &box_blur);

    ImGui::End();
    this->update_frame();

    if (edge_detect) {
        filter::edge_detect(frame);
    }   

    if (fry) {
        filter::fry(frame);
    }   

    this->texture.update_texture(frame);
}

bool MainScreen::init() {
    this->cap = cv::VideoCapture(0);
    if (!this->cap.isOpened()) {
        LOG("Failed to open camera");
        return false;
    }

    this->update_frame();
    while (this->frame.empty()) {
        LOG("dropping initial empty frames");
        this->update_frame();
    }

    this->texture.setup_texture(frame);
    this->setup_buffers();
    return true;
}
void MainScreen::quit() {
    this->cap.release();
    glDeleteVertexArrays(1, &this->vao);
}

}; // namespace self
