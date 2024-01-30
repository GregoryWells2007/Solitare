#pragma once
#include "engine_api.h"
#include "src/types/vector2.h"
#include "texture_2d_enums.h"

typedef struct texture_2d texture_2d;
struct platform_texture_2d;
void platform_texture_2d_generate(texture_2d* texture);
void platform_texture_2d_set_param(texture_2d_parameter param, texture_2d_parameter_value inpu);
void platform_texture_2d_bind(texture_2d* texture, int slot);
void platform_texture_2d_set_data(texture_2d* texture);

typedef struct texture_2d {
    int2 texture_size;
    texture_2d_color_mode color_mode;
    void* data;

    struct platform_texture_2d* platform_texture_2d;

    texture_2d_parameter_value* values;
} texture_2d;

HEADER_DEF texture_2d texture_2d_create() {
    texture_2d new_texture_2d = (texture_2d){ };
    new_texture_2d.texture_size = (int2){ 0, 0 };
    new_texture_2d.color_mode = texture_2d_color_mode_none;
    new_texture_2d.data = NULL;
    new_texture_2d.platform_texture_2d = NULL;

    new_texture_2d.values = malloc(sizeof(texture_2d_parameter_value) * texture_2d_parameter_none);
    return new_texture_2d;
}

HEADER_DEF void texture_2d_set_parameter(texture_2d* texture, texture_2d_parameter param, texture_2d_parameter_value input) { texture->values[param] = input; }

HEADER_DEF void texture_2d_set_width(texture_2d* texture, int width) { texture->texture_size.x = width; }
HEADER_DEF void texture_2d_set_height(texture_2d* texture, int height) { texture->texture_size.y = height; }
HEADER_DEF void texture_2d_set_size(texture_2d* texture, int width, int height) { 
    texture->texture_size.x = width; 
    texture->texture_size.x = height; 
}

HEADER_DEF void texture_2d_bind(texture_2d* texture, int slot) { platform_texture_2d_bind(texture, slot); }

HEADER_DEF void texture_2d_set_color_mode (texture_2d* texture, texture_2d_color_mode color_mode) { texture->color_mode = color_mode; }
HEADER_DEF void texture_2d_set_data(texture_2d* texture, void* data) { texture->data = data; }
HEADER_DEF void texture_2d_build(texture_2d* texture) {
    platform_texture_2d_generate(texture);
    platform_texture_2d_bind(texture, 0);

    for (int i = 0; i < texture_2d_parameter_none; i++)
        platform_texture_2d_set_param(i, texture->values[i]);

    platform_texture_2d_set_data(texture);
}