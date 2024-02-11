#include "board_renderer.h"
#include "stdio.h"

struct board_vertex {
    float x, y;
    float u, v;
};

void board_renderer_create_mesh(board_renderer* renderer) {
    struct board_vertex vertices[4] = {
        { -1.0f,  1.0f, 0.0f, 1.0f },
        { -1.0f, -1.0f, 0.0f, 0.0f },
        {  1.0f, -1.0f, 1.0f, 0.0f },
        {  1.0f,  1.0f, 1.0f, 1.0f },
    };
    triangle triangles[2] = {
        { 0, 1, 2 },
        { 0, 3, 2 }
    };

    renderer->board_vertex_array = vertex_array_create();

    renderer->board_positions_buffer = array_buffer_create(); 
    array_buffer_set_data(&renderer->board_positions_buffer, vertices);
    array_buffer_set_vertex_count(&renderer->board_positions_buffer, 4);
    array_buffer_set_draw_type(&renderer->board_positions_buffer, static_draw);   

    vertex_attribute positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->board_positions_buffer, &positions_attribute);

    vertex_attribute uv_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->board_positions_buffer, &uv_attribute);

    renderer->board_index_buffer = index_buffer_create();
    index_buffer_set_data(&renderer->board_index_buffer, triangles);
    index_buffer_set_triangle_count(&renderer->board_index_buffer, 2);
    index_buffer_set_draw_type(&renderer->board_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&renderer->board_vertex_array, &renderer->board_positions_buffer);
    vertex_array_set_index_buffer(&renderer->board_vertex_array, &renderer->board_index_buffer);

    vertex_array_build(&renderer->board_vertex_array);
}

void board_renderer_create_shader(board_renderer* renderer) {
    file vertex_shader_file = file_load_from_path("../res/shaders/board_shader/board_shader_vertex.glsl");
    file fragment_shader_file = file_load_from_path("../res/shaders/board_shader/board_shader_fragment.glsl");

    renderer->board_shader = shader_program_create();

    renderer->board_vertex_shader = shader_stage_create();
    shader_stage_set_type(&renderer->board_vertex_shader, vertex_shader);
    shader_stage_set_source(&renderer->board_vertex_shader, file_get_data(&vertex_shader_file));
    
    renderer->board_fragment_shader = shader_stage_create();
    shader_stage_set_type(&renderer->board_fragment_shader, fragment_shader);
    shader_stage_set_source(&renderer->board_fragment_shader, file_get_data(&fragment_shader_file));
    
    shader_program_set_stage(&renderer->board_shader, &renderer->board_vertex_shader);
    shader_program_set_stage(&renderer->board_shader, &renderer->board_fragment_shader);
    
    int texture_index = 1;
    renderer->texture_index_uniform = (shader_uniform){ &texture_index, "texture_index", uniform_int1  };

    shader_program_build(&renderer->board_shader);

    shader_program_bind(&renderer->board_shader);
    shader_program_set_uniform(&renderer->board_shader, &renderer->texture_index_uniform);
    shader_program_bind(NULL);
}

void board_renderer_init(board_renderer* renderer) {
    board_renderer_create_mesh(renderer);
    board_renderer_create_shader(renderer);
}

void board_renderer_init_board(board_renderer* renderer, board* board) {
    board->board_rendering_data.board_background_image = texture_2d_create();
    texture_2d_set_parameter(&board->board_rendering_data.board_background_image, texture_2d_magnification_filter, texture_2d_filter_nearest);
    texture_2d_set_parameter(&board->board_rendering_data.board_background_image, texture_2d_minification_filter, texture_2d_filter_nearest);

    texture_2d_set_parameter(&board->board_rendering_data.board_background_image, texture_2d_wrap_x, texture_2d_wrap_repeat);
    texture_2d_set_parameter(&board->board_rendering_data.board_background_image, texture_2d_wrap_y, texture_2d_wrap_repeat);

    texture_file cards_texture_file = texture_file_load_from_path(board->background_image);
    texture_2d_set_width(&board->board_rendering_data.board_background_image, cards_texture_file.width);
    texture_2d_set_height(&board->board_rendering_data.board_background_image, cards_texture_file.height);

    texture_2d_set_color_mode(&board->board_rendering_data.board_background_image, RGBA);
    texture_2d_set_data(&board->board_rendering_data.board_background_image, cards_texture_file.pixel_data);

    texture_2d_build(&board->board_rendering_data.board_background_image);
}

void board_renderer_draw_board(board_renderer* renderer, board* board) {
    texture_2d_bind(&board->board_rendering_data.board_background_image, 1);
    shader_program_bind(&renderer->board_shader);

    vertex_array_bind(&renderer->board_vertex_array);
    vertex_array_draw(&renderer->board_vertex_array);
}

void board_renderer_cleanup(board_renderer* renderer) {
    vertex_array_delete(&renderer->board_vertex_array);
}