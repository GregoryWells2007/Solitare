#version 330 core

out vec4 color;
in vec2 v_uv;

uniform sampler2D texure;

// data i need from shades
ivec2 card_texture_size = ivec2(13, 4);

ivec2 calc_from_1d_index(int index) {
    ivec2 return_value = ivec2(0);
    return_value.x = int(mod(index, card_texture_size.x));
    return_value.y = index / card_texture_size.x;
    return return_value;
}

void main(void) {
    ivec2 card_index = calc_from_1d_index(26);

    vec2 uv = vec2((v_uv.x + card_index.x) / card_texture_size.x, (v_uv.y + card_index.y) / card_texture_size.y);
    color = texture(texure, uv);
} 