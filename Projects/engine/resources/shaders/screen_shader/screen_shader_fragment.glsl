#version 330 core

out vec4 color;

in vec2 vUV;
uniform sampler2D texure;

uniform float vignette_size;
uniform float vignette_power;

void main(void) {
	vec2 uv = (1.0 - vUV) * vUV;
   float vignette_coverage = uv.x * uv.y * 15.0;
   float vignette_filter = pow(vignette_coverage, 0.25);

   color = texture(texure, vUV) * vec4(vec3(vignette_filter), 1.0); 
}