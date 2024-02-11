#version 330 core

out vec4 color;
in vec2 v_uv;

uniform sampler2D texture_index;

void main(void) {
    color = texture(texture_index, v_uv);
} 