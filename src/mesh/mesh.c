#include "mesh.h"
#include "stdio.h"

mesh create_mesh(mesh_data data) {
    unsigned int rendererID;

    glCreateBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.vertex_count, data.vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
    glEnableVertexAttribArray(0);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    mesh created_mesh = {};
    created_mesh.rendererID = rendererID;
    return created_mesh;
}

void draw_mesh(mesh* data) {
    printf("RendererID: %i\n", data->rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, data->rendererID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}