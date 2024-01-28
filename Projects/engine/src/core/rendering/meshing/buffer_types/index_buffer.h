#pragma once
#include "engine_api.h"
#include "../buffer_enums.h"

typedef struct index_buffer index_buffer;
struct platform_index_buffer;
void platform_index_buffer_build(index_buffer* buffer);
void platform_index_buffer_delete(index_buffer* buffer);

typedef struct index_buffer {
    void** data;
    int triangle_count;

    buffer_draw_type draw_type;

    struct platform_index_buffer* platform_index_buffer;
} index_buffer;

HEADER_DEF index_buffer index_buffer_create() {
    index_buffer new_index_buffer = (index_buffer){ };
    new_index_buffer.data = NULL;
    new_index_buffer.draw_type = none;
    return new_index_buffer;
}

HEADER_DEF void index_buffer_set_data(index_buffer* buffer, void* data) { buffer->data = data; }
HEADER_DEF void index_buffer_set_triangle_count(index_buffer* buffer, int count) { buffer->triangle_count = count; }
HEADER_DEF void index_buffer_set_draw_type(index_buffer* buffer, buffer_draw_type draw_type) { buffer->draw_type = draw_type; }

HEADER_DEF void index_buffer_build(index_buffer* buffer) {
    platform_index_buffer_build(buffer);
}

HEADER_DEF void index_buffer_delete(index_buffer* buffer) {
    platform_index_buffer_delete(buffer);
    free(buffer->platform_index_buffer);
}