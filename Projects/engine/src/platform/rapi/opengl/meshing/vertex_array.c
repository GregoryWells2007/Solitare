#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/meshing/vertex_array.h"
#include "glad/glad.h"

struct platform_vertex_array {
    unsigned int rendererID;
};

void platform_vertex_array_build(veretx_array* array) {
    array->platform_vertex_array = malloc(sizeof(struct platform_vertex_array));

    glGenVertexArrays(1, &array->platform_vertex_array->rendererID);
    glBindVertexArray(array->platform_vertex_array->rendererID);
}

void platform_vertex_array_delete(veretx_array* array) {
    glDeleteVertexArrays(1, &array->platform_vertex_array->rendererID);
}

#endif