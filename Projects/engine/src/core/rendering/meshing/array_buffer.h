#pragma once
#include "engine_api.h"

typedef struct array_buffer {
    void* data;
} array_buffer;

HEADER_DEF array_buffer array_buffer_create() {
    array_buffer new_array_buffer = (array_buffer){ };
    return new_array_buffer;
}

HEADER_DEF void array_buffer_set_data(array_buffer* buffer, void* data) { buffer->data = data; }