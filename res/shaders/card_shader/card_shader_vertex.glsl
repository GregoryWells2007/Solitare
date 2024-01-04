#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

uniform mat4 transformMatrix;
uniform mat4 cameraMatrix;

out vec2 vUV;

void main(void) {
    vUV = uv;
    gl_Position = cameraMatrix * transformMatrix * vec4(position, 1.0, 1.0);
}