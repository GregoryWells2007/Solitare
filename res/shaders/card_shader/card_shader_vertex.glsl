#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 card_data;

uniform mat4 camera_matrix;

out vec3 card_draw_data;
out vec2 v_uv;

void main(void) {
    v_uv = uv;
    card_draw_data = card_data;
    gl_Position = camera_matrix * vec4(position, 0.0, 1.0);
}