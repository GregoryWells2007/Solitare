#pragma once
#include "engine_api.h"
#include "buffer_types/array_buffer.h"
#include "buffer_types/index_buffer.h"

typedef struct veretx_array veretx_array;

struct platform_vertex_array;
void platform_vertex_array_build(veretx_array* array);
void platform_vertex_array_delete(veretx_array* array);

typedef struct veretx_array {
    array_buffer** array_buffers;
    int array_buffer_count;

    struct platform_vertex_array* platform_vertex_array;

    index_buffer* index_buffer;
} vertex_array;

HEADER_DEF vertex_array vertex_array_create() {
    vertex_array new_vertex_array = (vertex_array){ NULL, 0, NULL, NULL };
    return new_vertex_array;
}

HEADER_DEF void vertex_array_build(vertex_array* array) {
    platform_vertex_array_build(array);
}

HEADER_DEF void vertex_array_delete(vertex_array* array) {
    platform_vertex_array_delete(array);
    
    free(array->index_buffer);
    free(array->platform_vertex_array);
    free(array->array_buffers);
}