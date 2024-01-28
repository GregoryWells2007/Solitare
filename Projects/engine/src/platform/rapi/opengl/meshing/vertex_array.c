#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/meshing/vertex_array.h"
#include "glad/glad.h"

struct platform_vertex_array {
    unsigned int rendererID;
};

struct platform_index_buffer {
    unsigned int rendererID;
};

void platform_vertex_array_build(vertex_array* array) {
    array->platform_vertex_array = malloc(sizeof(struct platform_vertex_array));

    glGenVertexArrays(1, &array->platform_vertex_array->rendererID);
    glBindVertexArray(array->platform_vertex_array->rendererID);

    int max_attribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);

    int current_indes = 0;
    for (int i = 0; i < array->array_buffer_count; i++) {
        array_buffer* curr_array_buffer = array->array_buffers[i];
        for (int c = 0; c < curr_array_buffer->attribute_count; c++) {
            if (current_indes == max_attribs) {
                printf("You have too many vertex attribs the max is%i\n", max_attribs);
                return;
            }

            glEnableVertexArrayAttrib(array->platform_vertex_array->rendererID, current_indes);

            current_indes++;
        }
    }
}

void platform_vertex_array_draw(vertex_array* array) {
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(array->platform_vertex_array->rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, array->index_buffer->platform_index_buffer->rendererID);
    
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
}

void platform_vertex_array_delete(vertex_array* array) {
    glDeleteVertexArrays(1, &array->platform_vertex_array->rendererID);
}

#endif