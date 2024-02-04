#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/textures/texture_2d/texture_2d.h"
#include "glad/glad.h"

#include "texture_2d_platform.h"

void platform_texture_2d_generate(texture_2d* texture) {
    unsigned int rendererID;
    
    glGenTextures(1, &rendererID);

    texture->platform_texture_2d = malloc(sizeof(struct platform_texture_2d));
    texture->platform_texture_2d->rendererID = rendererID;
}

GLenum texture_2d_parameter_to_opengl(texture_2d_parameter param) {
    switch (param)
    {
    case texture_2d_magnification_filter: return GL_TEXTURE_MIN_FILTER;
    case texture_2d_minification_filter: return GL_TEXTURE_MAG_FILTER;
    case texture_2d_wrap_x: return GL_TEXTURE_WRAP_S;
    case texture_2d_wrap_y: return GL_TEXTURE_WRAP_T;
    }
}

GLenum texture_2d_parameter_value_to_opengl(texture_2d_parameter_value input) {
    switch (input)
    {
    case texture_2d_filter_nearest: return GL_NEAREST;
    case texture_2d_filter_linear: return GL_LINEAR;
    case texture_2d_wrap_repeat: return GL_REPEAT;
    case texture_2d_wrap_clamp: return GL_CLAMP;
    }
}

GLenum texture_2d_texture_2d_color_mode_to_opengl_format(texture_2d_color_mode input) {
    switch (input)
    {
    case RGBA: return GL_RGBA;
    case DEPTHSTENCIL: return GL_DEPTH_STENCIL;
    }
}

void platform_texture_2d_set_param(texture_2d_parameter param, texture_2d_parameter_value input) {
    glTexParameteri(GL_TEXTURE_2D, texture_2d_parameter_to_opengl(param), texture_2d_parameter_value_to_opengl(input));
}
void platform_texture_2d_bind(texture_2d* texture, int slot) {
    if (!texture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    } else {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture->platform_texture_2d->rendererID);
    }
}
void platform_texture_2d_set_data(texture_2d* texture) {        
    glTexImage2D(GL_TEXTURE_2D, 0, 
        texture_2d_texture_2d_color_mode_to_opengl_internal(texture->color_mode), texture->texture_size.x, texture->texture_size.y, 0, 
        texture_2d_texture_2d_color_mode_to_opengl_format(texture->color_mode), 
        GL_UNSIGNED_BYTE, 
        texture->data);
}

void platform_texture_2d_delete(texture_2d* texture) {
    glDeleteTextures(1, &texture->platform_texture_2d->rendererID);
}

#endif