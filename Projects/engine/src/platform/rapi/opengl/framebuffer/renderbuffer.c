#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/framebuffer/renderbuffer/renderbuffer.h"
#include "glad/glad.h"
#include "../textures/texture_2d/texture_2d_platform.h"
#include "renderbuffer_platform.h"

void platform_renderbuffer_build(renderbuffer* buffer) {
    unsigned int rendererID;

    glBindRenderbuffer(GL_RENDERBUFFER, rendererID);
    glRenderbufferStorage(GL_RENDERBUFFER, texture_2d_texture_2d_color_mode_to_opengl_internal(buffer->renderbuffer_color_mode), buffer->renderbuffer_size.x, buffer->renderbuffer_size.y); 

    buffer->platform_renderbuffer = malloc(sizeof(struct platform_renderbuffer));
    buffer->platform_renderbuffer->rendererID = rendererID;
}

void platform_renderbuffer_bind(renderbuffer* buffer) {
    if (buffer == NULL)
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    else
        glBindRenderbuffer(GL_RENDERBUFFER, buffer->platform_renderbuffer->rendererID);
}

void platform_renderbuffer_delete(renderbuffer* buffe) {

}

#endif