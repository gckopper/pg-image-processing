#version 330 core
layout (location = 0) in vec2 position;

out vec2 tex_coord;

void main() {
    // 2D only
    gl_Position = vec4(position.xy, 1.0, 1.0);
    tex_coord = vec2((position.x+1.0)/2.0, 1.0 - ((position.y+1.0)/2.0));
};
