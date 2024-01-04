#version 330 core

out vec4 color;
in vec2 v_uv;

uniform sampler2D texure;

void main(void) {
    color = texture(texure, v_uv);
} 