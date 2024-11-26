#version 330 core
// fixed attributes
layout (location = 0) in vec2 position;

// attributes that vary per instance
layout (location = 1) in vec3 delta_pos;
layout (location = 2) in vec2 scale;
layout (location = 3) in int i_tex_idx;

out vec2 tex_coord;
flat out int tex_idx;

void main() {
    
    mat2 rot = mat2(
         cos(delta_pos.z), -sin(delta_pos.z),
         sin(delta_pos.z),  cos(delta_pos.z)
    );


    vec2 temp = position * scale;
    temp *= rot;
    temp += delta_pos.xy;
    // 2D only
    gl_Position = vec4(temp, 1.0, 1.0);
    tex_coord = vec2((position.x+1.0)/2.0, 1.0 - ((position.y+1.0)/2.0));
    tex_idx = i_tex_idx;
}
