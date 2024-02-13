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
    case vertex_attribute_type_int: return GL_INT;
    }
}

void platform_array_buffer_build(array_buffer* buffer) {
    unsigned int rendererID;

    size_t size_of_vertex = 0;
    for (int i = 0; i < buffer->attribute_count; i++) {
        vertex_attribute* attribure = buffer->attributes[i];
        size_of_vertex += get_size_of_type(attribure->attribute_type) * attribure->count;
    }

    glCreateBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, size_of_vertex * buffer->vertex_count, buffer->data, (buffer->draw_type == static_draw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    size_t current_offset = 0;

    for (int i = 0; i < buffer->attribute_count; i++) {
        vertex_attribute* attribure = buffer->attributes[i];
        glVertexAttribPointer(i, attribure->count, platform_get_type(attribure->attribute_type), GL_FALSE, size_of_vertex, (const void*)current_offset);

        size_t type_size = get_size_of_type(attribure->attribute_type); 
        current_offset += type_size * attribure->count;
    }

    
    
    buffer->platform_array_buffer = malloc(sizeof(struct platform_array_buffer));
    buffer->platform_array_buffer->rendererID = rendererID;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void platform_array_buffer_draw(array_buffer* buffer) {
    glDrawArrays(GL_TRIANGLES, 0, buffer->vertex_count);
}

void platform_array_buffer_bind(array_buffer* buffer) {
    if (!buffer)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    else
        glBindBuffer(GL_ARRAY_BUFFER, buffer->platform_array_buffer->rendererID);
}

void platform_array_buffer_delete(array_buffer* buffer) {
    glDeleteBuffers(1, &buffer->platform_array_buffer->rendererID);
}

void platform_array_buffer_reallocate(array_buffer* buffer, size_t new_size, void* new_data) {
    printf("allocating new buffer\n");

    glBindBuffer(GL_ARRAY_BUFFER, buffer->platform_array_buffer->rendererID);
    glBufferData(GL_ARRAY_BUFFER, new_size, NULL, (buffer->draw_type == static_draw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, new_size, NULL, (buffer->draw_type == static_draw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW); // dont ask why i call it twice
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void platform_array_buffer_set_sub_data(array_buffer* buffer, size_t offset, void* data, size_t size) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer->platform_array_buffer->rendererID);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#endif