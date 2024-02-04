#pragma once
#include "engine_api.h"

struct platform_texture_2d {
    unsigned int rendererID;
};

HEADER_DEF GLenum texture_2d_texture_2d_color_mode_to_opengl_internal(texture_2d_color_mode input) {
    switch (input)
    {
    case RGBA: return GL_RGBA8;
    case DEPTHSTENCIL: return GL_DEPTH24_STENCIL8;
    }
}