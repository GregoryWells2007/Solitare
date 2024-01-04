#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stbimage.h"
#include "glad/glad.h"

typedef struct image_data {
    uint8_t* pixels;
    int width;
    int height;
} image_data;

image_data load_image(char* path) {
    image_data data = { };

    int width, height, channels;

    stbi_set_flip_vertically_on_load(1);
    unsigned char *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    assert(image != NULL);

    data.pixels = malloc(width * height * 4);
    memcpy(data.pixels, image, width * height * 4);
    data.width = width;
    data.height = height; 

    stbi_image_free(image);
    return data;
}

image load_image_from_file(char* path) {
    
    image_data data = load_image(path);
    
    unsigned int rendererID;
    glGenTextures(1, &rendererID);
    glBindTexture(GL_TEXTURE_2D, rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.pixels);

    return (image){rendererID};
}