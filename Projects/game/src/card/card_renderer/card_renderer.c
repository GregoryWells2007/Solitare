#include "card_renderer.h"

void card_renderer_init_shaders(card_renderer* renderer) {
    file vertex_shader_file = file_load_from_path("../res/shaders/card_shader/card_shader_vertex.glsl");
    file fragment_shader_file = file_load_from_path("../res/shaders/card_shader/card_shader_fragment.glsl");

    renderer->card_shader = shader_program_create();

    renderer->triangle_vertex_shader = shader_stage_create();
    shader_stage_set_type(&renderer->triangle_vertex_shader, vertex_shader);
    shader_stage_set_source(&renderer->triangle_vertex_shader, file_get_data(&vertex_shader_file));
    
    renderer->triangle_fragment_shader = shader_stage_create();
    shader_stage_set_type(&renderer->triangle_fragment_shader, fragment_shader);
    shader_stage_set_source(&renderer->triangle_fragment_shader, file_get_data(&fragment_shader_file));
    
    shader_program_set_stage(&renderer->card_shader, &renderer->triangle_vertex_shader);
    shader_program_set_stage(&renderer->card_shader, &renderer->triangle_fragment_shader);

    shader_program_build(&renderer->card_shader);
}
void card_renderer_create_uniforms(card_renderer* renderer) {
    int card_index = 0;
    int mouse_over = false;
    int card_held = false;
    renderer->card_index_uniform = (shader_uniform){ &card_index, "u_card_index", uniform_int1 };
    renderer->mouse_over_uniform = (shader_uniform){ &mouse_over, "mouse_over", uniform_int1 };
    renderer->card_held_uniform = (shader_uniform){ &card_held, "card_held", uniform_int1 };

    matrix4 empty_transform_matrix = matrix4_identity();

    renderer->camera_view_matrix = (shader_uniform){ &renderer->game_camera.camera_matrix, "camera_matrix", uniform_matrix4 };
    renderer->transform_matrix = (shader_uniform){ &empty_transform_matrix, "transform_matrix", uniform_matrix4 };

    shader_program_bind(&renderer->card_shader);
    shader_program_set_uniform(&renderer->card_shader, &renderer->card_index_uniform);
    shader_program_set_uniform(&renderer->card_shader, &renderer->mouse_over_uniform);
    shader_program_set_uniform(&renderer->card_shader, &renderer->card_held_uniform);
    shader_program_set_uniform(&renderer->card_shader, &renderer->camera_view_matrix);
    shader_program_set_uniform(&renderer->card_shader, &renderer->transform_matrix);
    shader_program_bind(NULL);
}
void card_renderer_create_camera(card_renderer* renderer) {
    // imma move this later
    renderer->game_camera = camera_create();
    camera_set_bounds(&renderer->game_camera, -640.0f, 640.0f, 360.0f, -360.0f);
    camera_set_position(&renderer->game_camera, (vector2){0.0f, 0.0f});
    camera_set_rotation(&renderer->game_camera, 0.0f);
}

struct card_vertex {
    float x, y;
    float u, v;
};

void card_renderer_create_vertex_array(card_renderer* renderer) {
    struct card_vertex vertices[24] = {
        { -1.000f,  1.750f,     0.0556f, 1.0000f },
        { -1.045f,  1.745f,     0.0356f, 0.9986f },
        { -1.075f,  1.735f,     0.0222f, 0.9957f },
        { -1.110f,  1.700f,     0.0067f, 0.9857f },
        { -1.120f,  1.670f,     0.0022f, 0.9771f },
        { -1.125f,  1.625f,     0.0000f, 0.9643f },
        
        { -1.125f, -1.625f,     0.0000f, 0.0357f },
        { -1.120f, -1.670f,     0.0022f, 0.0223f },
        { -1.110f, -1.700f,     0.0067f, 0.0143f },
        { -1.075f, -1.735f,     0.0222f, 0.0043f },
        { -1.045f, -1.745f,     0.0356f, 0.0014f },
        { -1.009f, -1.750f,     0.0556f, 0.0000f },

        {  1.000f, -1.750f,     0.9444f, 0.0000f },
        {  1.045f, -1.745f,     0.9644f, 0.0014f },
        {  1.075f, -1.735f,     0.9778f, 0.0043f },
        {  1.110f, -1.700f,     0.9933f, 0.0143f },
        {  1.120f, -1.670f,     0.9978f, 0.0223f },
        {  1.125f, -1.625f,     1.0000f, 0.0357f },

        {  1.125f,  1.625f,     1.0000f, 0.9643f },
        {  1.120f,  1.670f,     0.9978f, 0.9771f },
        {  1.110f,  1.700f,     0.9933f, 0.9857f },
        {  1.075f,  1.735f,     0.9778f, 0.9957f },
        {  1.045f,  1.745f,     0.9644f, 0.9986f },
        {  1.000f,  1.750f,     0.9444f, 1.0000f }
    };
    triangle triangles[22] = {
        { 0,  1, 22 },
        { 0, 23, 22 },

        { 1, 2, 21 },
        { 1, 22, 21 },

        { 2, 3, 20 },
        { 2, 21, 20 },

        { 3, 4, 19 },
        { 3, 20, 19 },

        { 4, 5, 18 },
        { 4, 19, 18 },

        { 5, 6, 17 },
        { 5, 18, 17 },

        { 6, 7, 16 },
        { 6, 17, 16 },

        { 7, 8, 15 },
        { 7, 16, 15 },

        { 8, 9, 14 },
        { 8, 15, 14 },

        { 9, 10, 13 },
        { 9, 14, 13 },

        { 10, 11, 12 },
        { 10, 13, 12 },
    };

    renderer->card_vertex_array = vertex_array_create();

    renderer->card_positions_buffer = array_buffer_create(); 
    array_buffer_set_data(&renderer->card_positions_buffer, vertices);
    array_buffer_set_vertex_count(&renderer->card_positions_buffer, 24);
    array_buffer_set_draw_type(&renderer->card_positions_buffer, static_draw);   

    vertex_attribute positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->card_positions_buffer, &positions_attribute);

    vertex_attribute uv_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->card_positions_buffer, &uv_attribute);

    renderer->card_index_buffer = index_buffer_create();
    index_buffer_set_data(&renderer->card_index_buffer, triangles);
    index_buffer_set_triangle_count(&renderer->card_index_buffer, 22);
    index_buffer_set_draw_type(&renderer->card_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&renderer->card_vertex_array, &renderer->card_positions_buffer);
    vertex_array_set_index_buffer(&renderer->card_vertex_array, &renderer->card_index_buffer);

    vertex_array_build(&renderer->card_vertex_array);
}

void card_renderer_init(card_renderer* renderer) {
    card_renderer_create_camera(renderer);

    card_renderer_init_shaders(renderer);
    card_renderer_create_uniforms(renderer);

    card_renderer_create_vertex_array(renderer);
}
void card_renderer_draw_card(card_renderer* renderer, vector2 position, int card_index) {
    shader_program_bind(&renderer->card_shader);
    

    matrix4 transform_matrix = matrix4_multiply(
        matrix4_translate((vector3){ position.x, position.y, 0.0 }), 
        matrix4_scale((vector3){ 60, 60, 1.0 })
    );

    renderer->card_index_uniform = (shader_uniform){ &card_index, "u_card_index", uniform_int1 };
    renderer->transform_matrix = (shader_uniform){ &transform_matrix, "transform_matrix", uniform_matrix4 };
    shader_program_update_uniform(&renderer->card_shader, &renderer->card_index_uniform);
    shader_program_update_uniform(&renderer->card_shader, &renderer->transform_matrix);

    vertex_array_bind(&renderer->card_vertex_array);
    vertex_array_draw(&renderer->card_vertex_array);
}
void card_renderer_cleanup(card_renderer* renderer) {
    shader_program_delete(&renderer->card_shader);
    vertex_array_delete(&renderer->card_vertex_array);
}