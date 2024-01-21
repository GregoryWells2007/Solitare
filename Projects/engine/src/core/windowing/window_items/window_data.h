#pragma once
#include "src/types/vector2.h"
#include "engine_api.h"

typedef struct window_data {
    char* title;
    vector2 size;
} window_data;

HEADER_DEF void window_data_set_name(window_data* data, char* value) { data->title = value; }
HEADER_DEF void window_data_set_size(window_data* data, vector2 value) { data->size = value; }