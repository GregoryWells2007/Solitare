#include "screen_renderer.h"
#include "src/types/vector3.h"
#include "stdio.h"

struct quad_vertex {
    float x, y;
};

void screen_renderder_init(screen_renderer* renderer) {
    float verts[8] = {
        -1.0,  1.0,
        -1.0, -1.0,
         1.0, -1.0,
         1.0,  1.0  
    };

    unsigned int tris[6] = {
        0, 1, 2,
        0, 3, 2
    };

    renderer->screen_vertex_array = vertex_array_create();

    renderer->screen_array_buffer = array_buffer_create(); 
    array_buffer_set_data(&renderer->screen_array_buffer, verts);
    array_buffer_set_vertex_count(&renderer->screen_array_buffer, 8);
    array_buffer_set_draw_type(&renderer->screen_array_buffer, static_draw);   

    renderer->screen_positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->screen_array_buffer, &renderer->screen_positions_attribute);

    renderer->screen_index_buffer = index_buffer_create();
    index_buffer_set_data(&renderer->screen_index_buffer, tris);
    index_buffer_set_triangle_count(&renderer->screen_index_buffer, 2);
    index_buffer_set_draw_type(&renderer->screen_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&renderer->screen_vertex_array, &renderer->screen_array_buffer);
    vertex_array_set_index_buffer(&renderer->screen_vertex_array, &renderer->screen_index_buffer);

    vertex_array_build(&renderer->screen_vertex_array);
}

void screen_renderder_draw(screen_renderer* renderer) {
    vertex_array_bind(&renderer->screen_vertex_array);
    vertex_array_draw(&renderer->screen_vertex_array);
}