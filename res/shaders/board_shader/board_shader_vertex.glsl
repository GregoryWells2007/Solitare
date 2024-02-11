#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

uniform bool is_background;
uniform mat4 transform_matrix;
uniform mat4 camera_matrix;

uniform int area_index;

out vec2 v_uv;

void main(void) {
    v_uv = uv;
    
    
    if (is_background) {
        gl_Position = vec4(position, 0.0, 1.0);
    }
    else {
        gl_Position = camera_matrix * transform_matrix * vec4(position, 0.0, 1.0);
        v_uv.x = (v_uv.x + area_index) / 6;
    }
}