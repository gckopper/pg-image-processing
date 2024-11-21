#include <self/main_screen.hpp>

namespace self {

void MainScreen::setup_buffers() {
    // clang-format off
    GLfloat vertices[] = {
        // x   y   
        -1.0, -1.0, 
         1.0, -1.0, 
        -1.0,  1.0,
         1.0,  1.0,
    };
    // clang-format on

    GLuint VBO;

    glGenVertexArrays(1, &this->vao);
    glCheckError();

    glBindVertexArray(this->vao);
    glCheckError();

    glGenBuffers(1, &VBO);
    glCheckError();
    glGenBuffers(1, &this->vbo);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glCheckError();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glCheckError();
    glEnableVertexAttribArray(0);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER,
                 MAX_STICKERS * sizeof(Transformation),
                 nullptr,
                 GL_DYNAMIC_DRAW);
    glCheckError();

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Transformation), (GLvoid*)0);
    glCheckError();

    glEnableVertexAttribArray(1);
    glCheckError();
    glVertexAttribDivisor(1, 1);
    glCheckError();

    glVertexAttribIPointer(2, 1, GL_INT, sizeof(Transformation), (GLvoid*)offsetof(Transformation, sticker));
    glCheckError();

    glEnableVertexAttribArray(2);
    glCheckError();
    glVertexAttribDivisor(2, 1);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();

    glBindVertexArray(0);
    glCheckError();
}

void MainScreen::update_frame() {
    if (this->image_path != nullptr) {
        return;
    }
    this->cap.read(this->frame);
}

void MainScreen::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glCheckError();
    glClear(GL_COLOR_BUFFER_BIT);
    glCheckError();

    glBindVertexArray(this->vao);
    glCheckError();

    for (Texture& t : this->textures) {
        t.bind();
    }
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->transformations.size());
    glCheckError();
    self::Texture::unbind();

    glBindVertexArray(0);
    glCheckError();
}

void MainScreen::render_ui() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainScreen::logic() {
    this->update_frame();

    cv::Mat modded = frame.clone();

    if (this->ui.grayscale) {
        filter::grayscale(modded);
    }

    if (this->ui.fry) {
        filter::fry(modded);
    }

    if (this->ui.bitwise_not) {
        filter::bitwise_not(modded);
    }

    if (this->ui.median_blur) {
        filter::median_blur(modded, this->ui.median_blur_ksize);
    }

    if (this->ui.gaussian) {
        filter::gaussian(modded, this->ui.gaussian_ksize);
    }

    if (this->ui.box_blur) {
        filter::box_filter(modded, this->ui.box_blur_ksize);
    }

    if (this->ui.wow) {
        filter::wow(modded);
    }

    if (this->ui.edge_detect) {
        filter::edge_detect(modded);
    }

    if (this->ui.canny) {
        filter::canny(modded);
    }

    if (this->ui.sharpen) {
        filter::sharpen(modded);
    }

    if (this->ui.save) {
        const std::chrono::time_point<std::chrono::system_clock> now =
            std::chrono::system_clock::now();
        std::string filename =
            std::format("Screenshot {0:%F} {0:%T}.webp", now);
        cv::Mat output(this->height, this->width, CV_8UC4, cv::Scalar(0));
        glReadPixels(0,
                     0,
                     this->width,
                     this->height,
                     GL_BGRA,
                     GL_UNSIGNED_BYTE,
                     output.data);
        cv::flip(output, output, 0);
        cv::imwrite(filename, output);
    }

    this->textures[0].update_texture(modded);
}

void MainScreen::update_ui() {
    {
        GLint dims[4] = {0};
        glGetIntegerv(GL_VIEWPORT, dims);
        this->width = dims[2];
        this->height = dims[3];
    }

    ImGui::Begin("Control");

    ImVec2 mouse_pos = ImGui::GetMousePos();

    if (ImGui::TreeNode("Filters")) {
        ImGui::Checkbox("Edge detection", &this->ui.edge_detect);
        ImGui::Checkbox("Fry", &this->ui.fry);
        ImGui::Checkbox("Bitwise not", &this->ui.bitwise_not);
        ImGui::Checkbox("Grayscale", &this->ui.grayscale);
        ImGui::Checkbox("WoW", &this->ui.wow);
        ImGui::Checkbox("Canny", &this->ui.canny);
        ImGui::Checkbox("Gaussian blur", &this->ui.gaussian);
        ImGui::SliderInt("Gaussian blur ksize",
                         &this->ui.gaussian_ksize,
                         1,
                         65,
                         "ksize = %d");
        this->ui.gaussian_ksize += 1 - this->ui.gaussian_ksize % 2;
        ImGui::Checkbox("Box blur", &this->ui.box_blur);
        ImGui::SliderInt(
            "Box blur ksize", &this->ui.box_blur_ksize, 1, 65, "ksize = %d");
        this->ui.box_blur_ksize += 1 - this->ui.box_blur_ksize % 2;
        ImGui::Checkbox("Median blur", &this->ui.median_blur);
        ImGui::SliderInt("Median blur ksize",
                         &this->ui.median_blur_ksize,
                         1,
                         65,
                         "ksize = %d");
        this->ui.median_blur_ksize += 1 - this->ui.median_blur_ksize % 2;
        ImGui::Checkbox("Sharpen", &this->ui.sharpen);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Stickers")) {
        for (int i = 0; i < sticker_names.size(); ++i) {
            if (ImGui::Button(sticker_names[i].data())) {
                Transformation t(0.0f, 0.0f, this->ui.scale, this->ui.rotation, i+1);
                if (transformations.size() < MAX_STICKERS) {
                    transformations.push_back(t);
                }
            }
        }
        ImGui::SliderFloat(
            "Scale", &this->ui.scale, 0.0f, 1.0f, "scale = %.3f");
        ImGui::SliderAngle(
            "Rotation", &this->ui.rotation, 0.0f, 360.0f, "rotation = %.3f");
        if (this->transformations.size() > 1) {
            this->transformations.back().scale = this->ui.scale;
            this->transformations.back().rot = this->ui.rotation;
        }
        ImGui::Button("Drag sticker");
        if (ImGui::IsItemActive() && !ImGui::IsItemHovered() && this->transformations.size() > 1) {
            transformations.back().x =
                ((2.0f * mouse_pos.x) / width) - 1.0f;
            transformations.back().y =
                -((2.0f * (mouse_pos.y)) / height) + 1.0f;
        }
        ImGui::TreePop();
    }
    this->ui.save = ImGui::Button("Save");

    ImGui::End();

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    this->transformations.size() * sizeof(Transformation),
                    this->transformations.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool MainScreen::init(int argc, char** argv) {
    uint8_t camera = 0;
    if (argc >= 2) {
        if (argv[1][0] == '\0') {
            LOG("First argument is null");
            return 3;
        };
        if (argv[1][0] >= '0' && argv[1][0] <= '9' && argv[1][1] == '\0') {
            camera = argv[1][0] - '0';
        } else {
            this->image_path = argv[1];
        }
    }

    if (this->image_path != nullptr) {
        self::load_image(this->image_path, this->frame);
        if (this->frame.empty()) {
            LOG("Unable to load image (" << this->image_path << ")");
            return false;
        }
        // remove alpha because it breaks the edge detection
        if (frame.type() == CV_8UC4) {
            cv::cvtColor(frame, frame, cv::COLOR_BGRA2BGR);
        }
    } else {
        this->cap = cv::VideoCapture(camera);
        if (!this->cap.isOpened()) {
            LOG("Failed to open camera");
            return false;
        }

        this->update_frame();
        while (this->frame.empty()) {
            LOG("dropping initial empty frames");
            this->update_frame();
        }
    }

    {
        int i = 1;
        for (const std::string_view& s : sticker_paths) {
            cv::Mat image;
            load_image(s.data(), image);
            this->textures[i].setup_texture(image, i);
            ++i;
        }
    }

    this->textures[0].setup_texture(this->frame, 0);

    this->transformations.emplace_back(0.0f, 0.0f, 1.0f, 0.0f, 0);

    this->setup_buffers();
    return true;
}

void MainScreen::quit() {
    this->cap.release();
    glDeleteVertexArrays(1, &this->vao);
}

}; // namespace self
