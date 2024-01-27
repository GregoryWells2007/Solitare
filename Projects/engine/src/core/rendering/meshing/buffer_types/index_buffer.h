#pragma once
#include "engine_api.h"
#include "../buffer_enums.h"

typedef struct index_buffer {
    void* data;
    buffer_draw_type draw_type;
} index_buffer;

HEADER_DEF index_buffer index_buffer_create() {
    index_buffer new_index_buffer = (index_buffer){ };
    new_index_buffer.data = NULL;
    new_index_buffer.draw_type = none;
    return new_index_buffer;
}

HEADER_DEF void index_buffer_set_data(index_buffer* buffer, void* data) { buffer->data = data; }
HEADER_DEF void index_buffer_set_draw_type(index_buffer* buffer, buffer_draw_type draw_type) { buffer->draw_type = draw_type; }