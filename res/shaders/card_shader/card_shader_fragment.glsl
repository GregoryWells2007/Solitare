#version 330 core

out vec4 color;
in vec2 v_uv;

uniform sampler2D texure;
uniform int u_card_index;

uniform int mouse_over;
uniform int card_held;

ivec2 card_texture_size = ivec2(13, 5);
ivec2 calc_from_1d_index(int index) {
    ivec2 return_value = ivec2(0);
    return_value.x = int(mod(index, card_texture_size.x));
    return_value.y = index / card_texture_size.x;
    return return_value;
}

vec3 base_color = vec3(1.0, 1.0, 1.0);
vec3 hover_color = vec3(0.75, 0.75, 0.75);
vec3 clicked_color = vec3(0.6, 0.6, 0.6);

vec4 get_color_multiplier() {
    ivec3 colors_to_use = ivec3(
        (1 - card_held) * (1 - mouse_over),
        mouse_over * (1 - card_held),
        card_held
    );

    vec3 finalColor = (base_color * colors_to_use.x) + (hover_color * colors_to_use.y) + (clicked_color * colors_to_use.z);
    return vec4(finalColor, 1.0);
} 

void main(void) {
    ivec2 card_index = calc_from_1d_index(u_card_index);
    
    vec2 uv = vec2((v_uv.x + card_index.x) / card_texture_size.x, (v_uv.y - (card_index.y + 1)) / card_texture_size.y);
    color = texture(texure, vec2(uv.x, uv.y));
} 