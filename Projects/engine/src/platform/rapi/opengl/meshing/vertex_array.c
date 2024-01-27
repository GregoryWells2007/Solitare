#include "engine_api.h"

#if RAPI == RAPI_OPENGL

#include "src/core/rendering/meshing/vertex_array.h"

struct platform_vertex_array {

};

void platform_vertex_array_build(veretx_array* array) {
    printf("building platform vertex array\n");
}

void platform_vertex_array_delete(veretx_array* array) {
    printf("deleting platform vertex array\n");
}

#endif