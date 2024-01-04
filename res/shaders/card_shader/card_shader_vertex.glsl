#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

uniform mat4 transformMatrix;

out vec2 vUV;

void main(void) {
    vUV = uv;

    vec2 new_position = (position * vec2(0.9, 1.6)) / vec2(4);
    gl_Position = transformMatrix * vec4(new_position, 1.0, 1.0);
}