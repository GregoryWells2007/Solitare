#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/framebuffer/framebuffer.h"
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

void platform_framebuffer_delete(framebuffer* buffer) {
    glDeleteFramebuffers(1, &buffer->platform_framebuffer->rendererID);
}

#endif