#version 330 core

in vec2 tex_coord;
flat in int tex_idx;

out vec4 color;

uniform sampler2D texture_uniform[6];

void main() {
    color = texture(texture_uniform[tex_idx], tex_coord);
}
