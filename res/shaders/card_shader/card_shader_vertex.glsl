#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

uniform mat4 transform_matrix;
uniform mat4 camera_matrix;

out vec2 v_uv;

void main(void) {
    v_uv = uv;
    gl_Position = camera_matrix * vec4(position, 0.0, 1.0);
}