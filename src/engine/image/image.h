#pragma once

typedef struct image {
    unsigned int rendererID;
} image;

image load_image_from_file(char* path);
void bind_image(image* image);