#pragma once

#ifdef DEBUG
#include <iostream>
#endif

#include <cstdlib>

#include <glad/gl.h>

#ifdef DEBUG
#define LOG(X) std::cerr << X << std::endl;
#else
#define LOG(X)
#endif

namespace self {

void log_shader(GLuint shader);
void log_program(GLuint program);
GLenum glCheckError_(const char* file, int line);

} // namespace self

#define glCheckError() self::glCheckError_(__FILE__, __LINE__)
