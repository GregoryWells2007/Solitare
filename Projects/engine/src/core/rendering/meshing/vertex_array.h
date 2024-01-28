#pragma once
#include "engine_api.h"
#include "buffer_types/array_buffer.h"
#include "buffer_types/index_buffer.h"

typedef struct veretx_array veretx_array;

struct platform_vertex_array;
void platform_vertex_array_build(veretx_array* array);
void platform_vertex_array_draw(veretx_array* array);
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

HEADER_DEF void vertex_array_add_array_buffer(vertex_array* array, array_buffer* buffer) {
    array->array_buffers = realloc(array->array_buffers, array->array_buffer_count + 1);
    array->array_buffers[array->array_buffer_count] = buffer;
    array->array_buffer_count++;
}

HEADER_DEF void vertex_array_set_index_buffer(vertex_array* array, index_buffer* buffer) {
    if (array->index_buffer != NULL) {
        printf("this vertex array already have an index buffer\n");
        return;
    }

    array->index_buffer = buffer;
}

HEADER_DEF void vertex_array_build(vertex_array* array) {
    platform_vertex_array_build(array);

    for (int i = 0; i < array->array_buffer_count; i++) {
        array_buffer_build(array->array_buffers[i]);
    }
}

HEADER_DEF void vertex_array_draw(vertex_array* array) {
    platform_vertex_array_draw(array);
}

HEADER_DEF void vertex_array_delete(vertex_array* array) {
    platform_vertex_array_delete(array);
    
    free(array->platform_vertex_array);

    for (int i = 0; i < array->array_buffer_count; i++)
        array_buffer_delete(array->array_buffers[i]);
}