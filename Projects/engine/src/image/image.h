#pragma once

typedef struct image {
    unsigned int rendererID;
    int slot;
} image;

image load_image_from_file(char* path);
void bind_image(image* image);
void set_bind_slot(image* image, int slot);