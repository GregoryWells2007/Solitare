#version 330 core

layout(location = 0) in vec2 position;



void main(void) {
    vec2 new_position = (position * vec2(0.9, 1.6)) / vec2(2);
    gl_Position = vec4(new_position, 1.0, 1.0);
}