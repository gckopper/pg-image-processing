#include <self/window.hpp>

#include <mainFragShader.h>
#include <mainVertShader.h>

GLFWwindow* setup_glfw(std::string_view title, int32_t height, int32_t width) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    auto key_callback =
        [](GLFWwindow* w, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(w, GL_TRUE);
        };
    auto resize = [] (GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    // Fazendo o registro da função de callback para a janela GLFW
    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, resize);

    // GLAD: carrega todos os ponteiros d funções da OpenGL
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        LOG("Failed to initialize OpenGL context");
        exit(-1);
    }
    const GLubyte* renderer =
        glGetString(GL_RENDERER);                     /* get renderer string */
    glCheckError();
    const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
    glCheckError();
    LOG("Renderer: " << renderer);
    LOG("OpenGL version supported " << version);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glCheckError();
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCheckError();
    glEnable(GL_BLEND);
    glCheckError();

    return window;
}

void setup_imgui(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(
        window, true); // Second param install_callback=true will install
                       // GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

namespace self {
void Window::setup(const std::string_view title,
                   const int32_t height,
                   const int32_t width) {
    this->window = setup_glfw(title, height, width);
    setup_imgui(this->window);

    GLint tex_uni;
    self::Shader shader;
    std::optional<GLuint> maybe_shader =
        shader.compile(VERT_SHADER, FRAG_SHADER);
    if (!maybe_shader.has_value()) {
        LOG("SHADER FAILURE");
        exit(2);
    }
    GLuint shaderID = maybe_shader.value();

    glUseProgram(shaderID);
    glCheckError();

    tex_uni = glGetUniformLocation(shaderID, "texture_uniform");
    glCheckError();
    int samplers[] = {0, 1, 2, 3, 4, 5}; 
    glUniform1iv(tex_uni, 6, samplers);
    glCheckError();
}

void Window::change_title(std::string_view title) {
    glfwSetWindowTitle(this->window, title.data());
}

void Window::get_input() { glfwPollEvents(); }

void Window::request_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::swap_buffers() { glfwSwapBuffers(this->window); }

void Window::close() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwTerminate();
}

bool Window::should_close() {
    return glfwWindowShouldClose(this->window);
}
} // namespace self
