// GLAD
#include <cstdlib>
#include <mainFragShader.h>
#include <mainVertShader.h>
#include <opencv2/opencv.hpp>

#include <glad/gl.h>

#include <self/log.hpp>
#include <self/shader.hpp>
#include <self/texture.hpp>
#include <self/window.hpp>
#include <self/screen.hpp>
#include <self/main_screen.hpp>

// GLFW
#include <GLFW/glfw3.h>

// ImGUI

#include <assert.h>

int main(int argc, char** argv) {
    self::Window window;
    window.setup("this nuts", 600, 800);

    GLint tex_uni;

    {
        // Compilando e buildando o programa de shader
        self::Shader shader;
        std::optional<GLuint> maybe_shader =
            shader.compile(VERT_SHADER, FRAG_SHADER);
        if (!maybe_shader.has_value()) {
            LOG("SHADER FAILURE");
            return 2;
        }
        GLuint shaderID = maybe_shader.value();

        glUseProgram(shaderID);
        glCheckError();

        tex_uni = glGetUniformLocation(shaderID, "texture_uniform");
        glCheckError();
        glUniform1i(tex_uni, 0);
        glCheckError();
    }

    self::MainScreen main_screen;

    if (!main_screen.init()) {
        LOG("Failed to init the main screen");
        return 3;
    }

    // Loop da aplicação - "game loop"
    while (!window.should_close()) {
        window.get_input();
        window.request_frame();

        main_screen.logic();
        
        main_screen.render();

        window.swap_buffers();
    }
    main_screen.quit();

    window.close();

    return 0;
}
