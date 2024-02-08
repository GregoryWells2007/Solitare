#version 330 core

out vec4 color;

in vec2 vUV;
uniform sampler2D texure;

void main(void) {
   color = texture(texure, vUV);
}