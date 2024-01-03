#version 330 core

out vec4 color;
in vec2 vUV;

void main(void) {
    color = vec4(vUV, 0.0, 1.0);
} 