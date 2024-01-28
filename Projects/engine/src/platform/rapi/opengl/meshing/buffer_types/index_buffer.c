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

    int* triangles = malloc(sizeof(int) * 3);
    triangles[0] = 0;
    triangles[1] = 1;
    triangles[2] = 2;

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3, triangles, GL_STATIC_DRAW);
    
    struct platform_index_buffer* new_buffer = malloc(sizeof(struct platform_index_buffer));
    new_buffer->rendererID = rendererID;
    buffer->platform_index_buffer = new_buffer;
}
void platform_index_buffer_delete(index_buffer* buffer) {
    glDeleteBuffers(1, &buffer->platform_index_buffer->rendererID);
}

#endif