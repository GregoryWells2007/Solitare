#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "glad/glad.h"
#include "src/core/rendering/meshing/buffer_types/array_buffer.h"

struct platform_array_buffer {
    unsigned int rendererID;
};

GLenum platform_get_type(vertex_attribute_type type) {
    switch (type) {
    case vertex_attribute_type_float: return GL_FLOAT;
    }
}

void platform_array_buffer_build(array_buffer* buffer) {
    unsigned int rendererID;

    glCreateBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer->data[0]) * buffer->vertex_count, buffer->data, GL_STATIC_DRAW);


    size_t current_offset = 0;
    size_t array_size = sizeof(buffer->data[0]);

    for (int i = 0; i < buffer->attribute_count; i++) {
        vertex_attribute* attribure = buffer->attributes[i];

        GLenum type = platform_get_type(attribure->attribute_type);

        glVertexAttribPointer(i, attribure->count, type, GL_FALSE, array_size, (const void*)current_offset);
    }
    
    
    buffer->platform_array_buffer = malloc(sizeof(struct platform_array_buffer));
    buffer->platform_array_buffer->rendererID = rendererID;
}

void platform_array_buffer_delete(array_buffer* buffer) {
    glDeleteBuffers(1, &buffer->platform_array_buffer->rendererID);
}

#endif