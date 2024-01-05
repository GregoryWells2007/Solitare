#include "mesh.h"
#include "stdio.h"

mesh create_mesh(mesh_data data) {
    unsigned int rendererID;
    unsigned int meshPositionsID;
    unsigned int indexBufferID;

    glGenVertexArrays(1, &rendererID);
    glBindVertexArray(rendererID);

    glCreateBuffers(1, &meshPositionsID);
    glBindBuffer(GL_ARRAY_BUFFER, meshPositionsID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.vertex_count, data.vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)0);
    glEnableVertexArrayAttrib(rendererID, 0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)(sizeof(float) * 2));
    glEnableVertexArrayAttrib(rendererID, 1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glCreateBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * data.triangle_count, data.triangles, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    mesh created_mesh = {};
    created_mesh.rendererID = rendererID;
    created_mesh.meshPositionsID = meshPositionsID;
    created_mesh.indexBufferID = indexBufferID;
    created_mesh.triangle_count = data.triangle_count;

    return created_mesh;
}

void draw_mesh(mesh* data) {
    glBindVertexArray(data->rendererID);

    glBindBuffer(GL_ARRAY_BUFFER, data->rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->indexBufferID);
    
    glDrawElements(GL_TRIANGLES, data->triangle_count, GL_UNSIGNED_INT, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}