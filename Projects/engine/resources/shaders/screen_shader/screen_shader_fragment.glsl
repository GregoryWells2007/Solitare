#version 330 core

out vec4 color;

in vec2 vUV;
uniform sampler2D texure;

uniform float vignette_power;
uniform bool use_vignette;

void main(void) {
	vec2 uv = (1.0 - vUV) * vUV;
   float vignette_coverage = uv.x * uv.y;
   float vignette_filter = pow(vignette_coverage, vignette_power);

   color = texture(texure, vUV); 
   if (use_vignette)
      color *= vec4(vec3(vignette_filter), 1.0);
}