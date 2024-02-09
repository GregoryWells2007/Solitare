#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stbimage.h"

typedef struct texture_file {
    uint8_t* pixel_data;
    int width, height;
} texture_file;

texture_file texture_file_load_from_path(char* path) {
    texture_file data = (texture_file){ };

    int width, height, channels;

    stbi_set_flip_vertically_on_load(1);
    unsigned char *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    assert(image != NULL);

    data.pixel_data = malloc(width * height * 4);
    memcpy(data.pixel_data, image, width * height * 4);
    data.width = width;
    data.height = height; 

    stbi_image_free(image);
    return data;
}