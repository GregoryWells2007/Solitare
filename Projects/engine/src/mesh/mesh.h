#pragma once
#include "glad/glad.h"

typedef struct mesh_data {
    float* vertex_positions;
    int vertex_count;

    int* triangles;
    int triangle_count;
} mesh_data;

typedef struct mesh {
    unsigned int rendererID;
    
    unsigned int meshPositionsID;
    unsigned int indexBufferID;

    int triangle_count;
} mesh;

mesh create_mesh(mesh_data data);
void draw_mesh(mesh* data);