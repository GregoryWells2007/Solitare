#pragma once
#include "engine_api.h"
#include "src/types/vector2.h"
#include "src/core/rendering/textures/texture_2d/texture_2d_enums.h"

typedef struct renderbuffer renderbuffer;
struct platform_renderbuffer;
void platform_renderbuffer_build(renderbuffer* buffer);
void platform_renderbuffer_bind(renderbuffer* buffer);
void platform_renderbuffer_delete(renderbuffer* buffer);

typedef struct renderbuffer {
    ivec2 renderbuffer_size;
    texture_2d_color_mode renderbuffer_color_mode;

    struct platform_renderbuffer* platform_renderbuffer;
} renderbuffer;

HEADER_DEF renderbuffer renderbuffer_create() {
    renderbuffer new_renderbuffer = (renderbuffer){ };
    new_renderbuffer.renderbuffer_size = (ivec2) { 0, 0 };
    return new_renderbuffer;
}

HEADER_DEF void renderbuffer_set_width(renderbuffer* buffer, int width) { buffer->renderbuffer_size.x = width; }
HEADER_DEF void renderbuffer_set_height(renderbuffer* buffer, int height) { buffer->renderbuffer_size.y = height; }
HEADER_DEF void renderbuffer_set_size(renderbuffer* buffer, int width, int height) { 
    buffer->renderbuffer_size.x = width; 
    buffer->renderbuffer_size.y = height; 
}

HEADER_DEF void renderbuffer_set_color_mode(renderbuffer* buffer, texture_2d_color_mode color_mode) { buffer->renderbuffer_color_mode = color_mode; }

HEADER_DEF void renderbuffer_bind(renderbuffer* buffer) { platform_renderbuffer_bind(buffer); }
HEADER_DEF void renderbuffer_build(renderbuffer* buffer) {
    platform_renderbuffer_build(buffer);
    renderbuffer_bind(NULL);
}   


HEADER_DEF void renderbuffer_delete(renderbuffer* buffer) {
    platform_renderbuffer_delete(buffer);
    free(buffer->platform_renderbuffer);
}