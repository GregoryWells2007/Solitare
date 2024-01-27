#pragma once
#include "engine_api.h"
#include "buffer_types/array_buffer.h"
#include "buffer_types/index_buffer.h"

typedef struct vertex_array {
    array_buffer** array_buffers;
    int array_buffer_count;

    index_buffer* index_buffer;
} vertex_array;

HEADER_DEF vertex_array vertex_array_create() {
    vertex_array new_vertex_array = (vertex_array){ };

    return new_vertex_array;
}