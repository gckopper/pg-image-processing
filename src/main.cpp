// GLAD
#include <cstdlib>
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

    self::MainScreen main_screen;

    if (!main_screen.init(argc, argv)) {
        LOG("Failed to init the main screen");
        return 3;
    }

    while (!window.should_close()) {
        window.get_input();
        window.request_frame();

        main_screen.render();
        
        main_screen.update_ui();

        if (!main_screen.logic()) {
            window.please_close();
        }

        main_screen.render_ui();

        window.swap_buffers();
    }
    main_screen.quit();

    window.close();

    return 0;
}
