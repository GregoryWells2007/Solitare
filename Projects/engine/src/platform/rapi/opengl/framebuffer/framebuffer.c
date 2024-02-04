#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/framebuffer/framebuffer.h"
#include "../textures/texture_2d/texture_2d_platform.h"
#include "glad/glad.h"

struct platform_framebuffer {
    unsigned int rendererID;
};

void platform_framebuffer_build(framebuffer* buffer) {
    unsigned int rendererID;
    glCreateFramebuffers(1, &rendererID);

    buffer->platform_framebuffer = malloc(sizeof(struct platform_framebuffer));
    buffer->platform_framebuffer->rendererID = rendererID;
}

void platform_framebuffer_bind(framebuffer* buffer) {
    if (buffer == NULL)
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    else    
        glBindFramebuffer(GL_FRAMEBUFFER, buffer->platform_framebuffer->rendererID);
}

GLenum platform_attachment_type_opengl(framebuffer_attachment_type attachment_type) {
    switch (attachment_type)
    {
    case color_attachment_0: return GL_COLOR_ATTACHMENT0;
    case depth_stencil_attachment: return GL_DEPTH_STENCIL_ATTACHMENT;
    }
}

void platform_framebuffer_add_attachment(framebuffer* buffer, framebuffer_attachment* attachment) {
    if (attachment->data_type == framebuffer_data_type_texture_2d) {
        texture_2d* texture = attachment->data;
        struct platform_texture_2d* tex = texture->platform_texture_2d;

        printf("%i, %i\n", platform_attachment_type_opengl(attachment->attachment_type), tex->rendererID);

        glFramebufferTexture2D(GL_FRAMEBUFFER, platform_attachment_type_opengl(attachment->attachment_type), GL_TEXTURE_2D, tex->rendererID, 0);
    } else {
        printf("RENDERBUFFER not supported at attachment type\n");
    }
}

void platform_framebuffer_delete(framebuffer* buffer) {
    glDeleteFramebuffers(1, &buffer->platform_framebuffer->rendererID);
}

#endif