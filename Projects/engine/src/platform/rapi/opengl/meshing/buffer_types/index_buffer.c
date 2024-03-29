#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "glad/glad.h"
#include "src/core/rendering/meshing/buffer_types/index_buffer.h"

#include "src/types/vector3.h"

struct platform_index_buffer {
    unsigned int rendererID;
};
void platform_index_buffer_build(index_buffer* buffer) {
    unsigned int rendererID;

    glCreateBuffers(1, &rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle) * buffer->triangle_count, buffer->data, (buffer->draw_type == static_draw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW );
    
    struct platform_index_buffer* new_buffer = malloc(sizeof(struct platform_index_buffer));
    new_buffer->rendererID = rendererID;
    buffer->platform_index_buffer = new_buffer;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void platform_index_buffer_bind(index_buffer* buffer) {
    if (!buffer)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    else
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->platform_index_buffer->rendererID);
}

void platform_index_buffer_delete(index_buffer* buffer) {
    glDeleteBuffers(1, &buffer->platform_index_buffer->rendererID);
}

#endif