#pragma once
#include "engine_api.h"
#include "../buffer_enums.h"

typedef struct index_buffer {
    void* data;
    buffer_draw_type draw_type;
} index_buffer;

index_buffer index_buffer_create() {
    index_buffer new_index_buffer = (index_buffer){ };
    new_index_buffer.data = NULL;
    new_index_buffer.draw_type = none;
    return new_index_buffer;
}