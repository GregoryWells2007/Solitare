#include "screen_renderer.h"
#include "src/types/vector3.h"
#include "stdio.h"
#include "src/core/utils/file.h"

void screen_renderer_create_mesh(screen_renderer* renderer) {
    float verts[16] = {
        -1.0,  1.0, 0.0, 1.0,
        -1.0, -1.0, 0.0, 0.0,
         1.0, -1.0, 1.0, 0.0,
         1.0,  1.0, 1.0, 1.0,
    };

    unsigned int tris[6] = {
        0, 1, 2,
        0, 3, 2
    };

    renderer->screen_mesh.screen_vertex_array = vertex_array_create();

    renderer->screen_mesh.screen_array_buffer = array_buffer_create(); 
    array_buffer_set_data(&renderer->screen_mesh.screen_array_buffer, verts);
    array_buffer_set_vertex_count(&renderer->screen_mesh.screen_array_buffer, 16);
    array_buffer_set_draw_type(&renderer->screen_mesh.screen_array_buffer, static_draw);   

    renderer->screen_mesh.screen_positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->screen_mesh.screen_array_buffer, &renderer->screen_mesh.screen_positions_attribute);

    renderer->screen_mesh.screen_uvs_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->screen_mesh.screen_array_buffer, &renderer->screen_mesh.screen_uvs_attribute);

    renderer->screen_mesh.screen_index_buffer = index_buffer_create();
    index_buffer_set_data(&renderer->screen_mesh.screen_index_buffer, tris);
    index_buffer_set_triangle_count(&renderer->screen_mesh.screen_index_buffer, 2);
    index_buffer_set_draw_type(&renderer->screen_mesh.screen_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&renderer->screen_mesh.screen_vertex_array, &renderer->screen_mesh.screen_array_buffer);
    vertex_array_set_index_buffer(&renderer->screen_mesh.screen_vertex_array, &renderer->screen_mesh.screen_index_buffer);

    vertex_array_build(&renderer->screen_mesh.screen_vertex_array);
}
void screen_renderer_create_shader(screen_renderer* renderer) {
    file vertex_shader_source = file_load_from_path("../Projects/engine/resources/shaders/screen_shader/screen_shader_vertex.glsl");
    file fragment_shader_source = file_load_from_path("../Projects/engine/resources/shaders/screen_shader/screen_shader_fragment.glsl");

    renderer->screen_shader.screen_shader = shader_program_create();

    renderer->screen_shader.screen_renderder_vertex_shader = shader_stage_create();
    shader_stage_set_type(&renderer->screen_shader.screen_renderder_vertex_shader, vertex_shader);
    shader_stage_set_source(&renderer->screen_shader.screen_renderder_vertex_shader, file_get_data(&vertex_shader_source));
    
    renderer->screen_shader.screen_renderer_fragment_shader = shader_stage_create();
    shader_stage_set_type(&renderer->screen_shader.screen_renderer_fragment_shader, fragment_shader);
    shader_stage_set_source(&renderer->screen_shader.screen_renderer_fragment_shader, file_get_data(&fragment_shader_source));
    
    shader_program_set_stage(&renderer->screen_shader.screen_shader, &renderer->screen_shader.screen_renderder_vertex_shader);
    shader_program_set_stage(&renderer->screen_shader.screen_shader, &renderer->screen_shader.screen_renderer_fragment_shader);

    shader_program_build(&renderer->screen_shader.screen_shader);
}

void screen_renderer_init(screen_renderer* renderer) {
    screen_renderer_create_mesh(renderer);
    screen_renderer_create_shader(renderer);

    shader_uniform vignette_power_uniform = (shader_uniform){ &renderer->screen_data.vignette_power, "vignette_power", uniform_float1 };
    shader_uniform vignette_power_uniform = (shader_uniform){ &renderer->screen_data.use_vignette, "vignette_power", uniform_bool };
}

void screen_renderer_draw(screen_renderer* renderer) {
    shader_program_bind(&renderer->screen_shader.screen_shader);

    vertex_array_bind(&renderer->screen_mesh.screen_vertex_array);
    vertex_array_draw(&renderer->screen_mesh.screen_vertex_array);
}

void screen_renderer_delete(screen_renderer* renderer) {
    vertex_array_delete(&renderer->screen_mesh.screen_vertex_array);
    shader_program_delete(&renderer->screen_shader.screen_shader);
}