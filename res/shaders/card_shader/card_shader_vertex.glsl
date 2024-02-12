#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in float card_index;

uniform mat4 camera_matrix;

out vec3 v_card_data;
out vec2 v_uv;

void main(void) {
    v_uv = uv;
    v_card_data = vec3(card_index, 0, 0);
    gl_Position = camera_matrix * vec4(position, 0.0, 1.0);
}