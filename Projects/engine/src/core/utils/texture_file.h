#pragma once
#include "engine_api.h"

typedef struct texture_file {
    uint8_t* pixel_data;
    int width, height;
} texture_file;

texture_file texture_file_load_from_path(char* path);