#pragma once
#include "engine_api.h"
#include "../buffer_enums.h"

typedef struct array_buffer {
    void* data;
    buffer_draw_type draw_type;

    
} array_buffer;

HEADER_DEF array_buffer array_buffer_create() {
    array_buffer new_array_buffer = (array_buffer){ };
    new_array_buffer.data = NULL;
    new_array_buffer.draw_type = none;
    return new_array_buffer;
}

HEADER_DEF void array_buffer_set_draw_type(array_buffer* buffer, buffer_draw_type new_draw_type) {
    buffer->draw_type = new_draw_type;
}
HEADER_DEF void array_buffer_set_data(array_buffer* buffer, void* data) { buffer->data = data; }