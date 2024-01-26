#pragma once
#include "engine_api.h"
#include "src/types/vector2.h"

typedef struct output_buffer_data {
    vector2 size;
} output_buffer_data;

HEADER_DEF void output_buffer_data_set_size(output_buffer_data* data, vector2 new_size) {
    data->size = new_size;
} 