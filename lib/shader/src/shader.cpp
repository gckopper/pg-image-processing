#include <self/shader.hpp>
#include <string>
#include "self/log.hpp"

namespace self {
std::optional<GLuint> Shader::compile(const std::string_view& vert_source, const std::string_view& frag_source) {
    // Vertex
    std::optional<GLuint> vert_shader =
        Shader::generic_compile(vert_source, GL_VERTEX_SHADER);
    if (!vert_shader.has_value()) {
        return std::nullopt;
    }
    // Fragment
    std::optional<GLuint> frag_shader =
        Shader::generic_compile(frag_source, GL_FRAGMENT_SHADER);
    if (!frag_shader.has_value()) {
        return std::nullopt;
    }

    GLint result = 0;
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vert_shader.value());
    glCheckError();

    glAttachShader(shaderProgram, frag_shader.value());
    glCheckError();

    glLinkProgram(shaderProgram);
    glCheckError();

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    glCheckError();
    if (!result) {
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &result);
        glCheckError();
        std::string log(result, ' ');
        glGetProgramInfoLog(shaderProgram, result, NULL, log.data());
        glCheckError();
        LOG("Shader linking failed with error: " << log);
        return std::nullopt;
    }

    return shaderProgram;
}

std::optional<GLuint> Shader::generic_compile(const std::string_view& source,
                                              GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    glCheckError();
    const GLchar* cstr_source = (const GLchar*)source.data();
    glShaderSource(shader, 1, &cstr_source, NULL);
    glCheckError();
    glCompileShader(shader);
    glCheckError();
    GLint result = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glCheckError();
    // compilation failed
    if (!result) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
        glCheckError();
        std::string log(result, ' ');
        glGetShaderInfoLog(shader, result, NULL, log.data());
        glCheckError();
        LOG("Shader compilation failed with error: " << log);
        return std::nullopt;
    }
    return shader;
}
} // namespace self
