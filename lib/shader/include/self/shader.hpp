#pragma once

#include <optional>
#include <string_view>

#include <glad/gl.h>

#include <self/log.hpp>

namespace self {

class Shader {
  public:
    std::optional<GLuint> compile(const std::string_view& vertex_source, const std::string_view& frag_source);

  private:
    std::optional<GLuint> generic_compile(const std::string_view& source,
                                          GLenum shader_type);
};

} // namespace self
