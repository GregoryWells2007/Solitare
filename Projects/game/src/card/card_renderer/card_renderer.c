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

    matrix4 empty_transform_matrix = matrix4_identity();

    renderer->camera_view_matrix = (shader_uniform){ &renderer->game_camera.camera_matrix, "camera_matrix", uniform_matrix4 };

    shader_program_bind(&renderer->card_shader);
    shader_program_set_uniform(&renderer->card_shader, &renderer->camera_view_matrix);
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
    ivec3 card_idata;
};

void card_renderer_create_vertex_array(card_renderer* renderer) {
    triangle triangles_template[22] = {
        { 0,  1, 22 },
        { 0, 23, 22 },

        { 1, 2, 21 },
        { 1, 22, 21 },
    };

    triangle triangles[22 * 100] = {};

    int offset = 0;
    for (int i = 0; i < (100 * 22); i += 22) {
        triangles[0 + i]  = (triangle) {  0 + offset,  1 + offset, 22 + offset };
        triangles[1 + i]  = (triangle) {  0 + offset, 23 + offset, 22 + offset };
        triangles[2 + i]  = (triangle) {  1 + offset,  2 + offset, 21 + offset };
        triangles[3 + i]  = (triangle) {  1 + offset, 22 + offset, 21 + offset };
        triangles[4 + i]  = (triangle) {  2 + offset,  3 + offset, 20 + offset };
        triangles[5 + i]  = (triangle) {  2 + offset, 21 + offset, 20 + offset };
        triangles[6 + i]  = (triangle) {  3 + offset,  4 + offset, 19 + offset };
        triangles[7 + i]  = (triangle) {  3 + offset, 20 + offset, 19 + offset };
        triangles[8 + i]  = (triangle) {  4 + offset,  5 + offset, 18 + offset };
        triangles[9 + i]  = (triangle) {  4 + offset, 19 + offset, 18 + offset };
        triangles[10 + i] = (triangle) {  5 + offset,  6 + offset, 17 + offset };
        triangles[11 + i] = (triangle) {  5 + offset, 18 + offset, 17 + offset };
        triangles[12 + i] = (triangle) {  6 + offset,  7 + offset, 16 + offset };
        triangles[13 + i] = (triangle) {  6 + offset, 17 + offset, 16 + offset };
        triangles[14 + i] = (triangle) {  7 + offset,  8 + offset, 15 + offset };
        triangles[15 + i] = (triangle) {  7 + offset, 16 + offset, 15 + offset };
        triangles[16 + i] = (triangle) {  8 + offset,  9 + offset, 14 + offset };
        triangles[17 + i] = (triangle) {  8 + offset, 15 + offset, 14 + offset };
        triangles[18 + i] = (triangle) {  9 + offset, 10 + offset, 13 + offset };
        triangles[19 + i] = (triangle) {  9 + offset, 14 + offset, 13 + offset };
        triangles[20 + i] = (triangle) { 10 + offset, 11 + offset, 12 + offset };
        triangles[21 + i] = (triangle) { 10 + offset, 13 + offset, 12 + offset };

        offset += 24;
    }

    renderer->card_vertex_array = vertex_array_create();

    renderer->card_positions_buffer = array_buffer_create(); 
    array_buffer_set_data(&renderer->card_positions_buffer, NULL);
    array_buffer_set_vertex_count(&renderer->card_positions_buffer, 24 * 100);
    array_buffer_set_draw_type(&renderer->card_positions_buffer, dynamic_draw);   

    vertex_attribute positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->card_positions_buffer, &positions_attribute);

    vertex_attribute uv_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&renderer->card_positions_buffer, &uv_attribute);

    vertex_attribute card_data_attribute = (vertex_attribute){ vertex_attribute_type_int, 3 };
    array_buffer_add_attribute(&renderer->card_positions_buffer, &card_data_attribute);

    renderer->card_index_buffer = index_buffer_create();
    index_buffer_set_data(&renderer->card_index_buffer, triangles);
    index_buffer_set_triangle_count(&renderer->card_index_buffer, 22 * 100);
    index_buffer_set_draw_type(&renderer->card_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&renderer->card_vertex_array, &renderer->card_positions_buffer);
    vertex_array_set_index_buffer(&renderer->card_vertex_array, &renderer->card_index_buffer);

    vertex_array_build(&renderer->card_vertex_array);
}

void card_renderer_create_texture(card_renderer* renderer) {
    renderer->cards_image = texture_2d_create();
    texture_2d_set_parameter(&renderer->cards_image, texture_2d_magnification_filter, texture_2d_filter_nearest);
    texture_2d_set_parameter(&renderer->cards_image, texture_2d_minification_filter, texture_2d_filter_nearest);

    texture_2d_set_parameter(&renderer->cards_image, texture_2d_wrap_x, texture_2d_wrap_repeat);
    texture_2d_set_parameter(&renderer->cards_image, texture_2d_wrap_y, texture_2d_wrap_repeat);

    texture_file cards_texture_file = texture_file_load_from_path("../res/images/Cards.png");
    texture_2d_set_width(&renderer->cards_image, cards_texture_file.width);
    texture_2d_set_height(&renderer->cards_image, cards_texture_file.height);

    texture_2d_set_color_mode(&renderer->cards_image, RGBA);
    texture_2d_set_data(&renderer->cards_image, cards_texture_file.pixel_data);

    texture_2d_build(&renderer->cards_image);
}

void card_renderer_init(card_renderer* renderer) {
    card_renderer_create_camera(renderer);

    card_renderer_init_shaders(renderer);
    card_renderer_create_uniforms(renderer);

    card_renderer_create_vertex_array(renderer);

    card_renderer_create_texture(renderer);
}
void card_renderer_draw_card(card_renderer* renderer, vector2 position, int card_index) {
    int CARD_SIZE = 40;

    struct card_vertex vertices[24] = {
        { (-1.000f * CARD_SIZE) + position.x,  (1.750f * CARD_SIZE) + position.y,     0.0556f, 1.0000f, (ivec3){ card_index, 0, 0 } },
        { (-1.045f * CARD_SIZE) + position.x,  (1.745f * CARD_SIZE) + position.y,     0.0356f, 0.9986f, (ivec3){ card_index, 0, 0 } },
        { (-1.075f * CARD_SIZE) + position.x,  (1.735f * CARD_SIZE) + position.y,     0.0222f, 0.9957f, (ivec3){ card_index, 0, 0 } },
        { (-1.110f * CARD_SIZE) + position.x,  (1.700f * CARD_SIZE) + position.y,     0.0067f, 0.9857f, (ivec3){ card_index, 0, 0 } },
        { (-1.120f * CARD_SIZE) + position.x,  (1.670f * CARD_SIZE) + position.y,     0.0022f, 0.9771f, (ivec3){ card_index, 0, 0 } },
        { (-1.125f * CARD_SIZE) + position.x,  (1.625f * CARD_SIZE) + position.y,     0.0000f, 0.9643f, (ivec3){ card_index, 0, 0 } },
        
        { (-1.125f * CARD_SIZE) + position.x, (-1.625f * CARD_SIZE) + position.y,     0.0000f, 0.0357f, (ivec3){ card_index, 0, 0 } },
        { (-1.120f * CARD_SIZE) + position.x, (-1.670f * CARD_SIZE) + position.y,     0.0022f, 0.0223f, (ivec3){ card_index, 0, 0 } },
        { (-1.110f * CARD_SIZE) + position.x, (-1.700f * CARD_SIZE) + position.y,     0.0067f, 0.0143f, (ivec3){ card_index, 0, 0 } },
        { (-1.075f * CARD_SIZE) + position.x, (-1.735f * CARD_SIZE) + position.y,     0.0222f, 0.0043f, (ivec3){ card_index, 0, 0 } },
        { (-1.045f * CARD_SIZE) + position.x, (-1.745f * CARD_SIZE) + position.y,     0.0356f, 0.0014f, (ivec3){ card_index, 0, 0 } },
        { (-1.009f * CARD_SIZE) + position.x, (-1.750f * CARD_SIZE) + position.y,     0.0556f, 0.0000f, (ivec3){ card_index, 0, 0 } },

        {  (1.000f * CARD_SIZE) + position.x, (-1.750f * CARD_SIZE) + position.y,     0.9444f, 0.0000f, (ivec3){ card_index, 0, 0 }  },
        {  (1.045f * CARD_SIZE) + position.x, (-1.745f * CARD_SIZE) + position.y,     0.9644f, 0.0014f, (ivec3){ card_index, 0, 0 }  },
        {  (1.075f * CARD_SIZE) + position.x, (-1.735f * CARD_SIZE) + position.y,     0.9778f, 0.0043f, (ivec3){ card_index, 0, 0 }  },
        {  (1.110f * CARD_SIZE) + position.x, (-1.700f * CARD_SIZE) + position.y,     0.9933f, 0.0143f, (ivec3){ card_index, 0, 0 }  },
        {  (1.120f * CARD_SIZE) + position.x, (-1.670f * CARD_SIZE) + position.y,     0.9978f, 0.0223f, (ivec3){ card_index, 0, 0 }  },
        {  (1.125f * CARD_SIZE) + position.x, (-1.625f * CARD_SIZE) + position.y,     1.0000f, 0.0357f, (ivec3){ card_index, 0, 0 }  },

        {  (1.125f * CARD_SIZE) + position.x,  (1.625f * CARD_SIZE) + position.y,     1.0000f, 0.9643f, (ivec3){ card_index, 0, 0 } },
        {  (1.120f * CARD_SIZE) + position.x,  (1.670f * CARD_SIZE) + position.y,     0.9978f, 0.9771f, (ivec3){ card_index, 0, 0 } },
        {  (1.110f * CARD_SIZE) + position.x,  (1.700f * CARD_SIZE) + position.y,     0.9933f, 0.9857f, (ivec3){ card_index, 0, 0 } },
        {  (1.075f * CARD_SIZE) + position.x,  (1.735f * CARD_SIZE) + position.y,     0.9778f, 0.9957f, (ivec3){ card_index, 0, 0 } },
        {  (1.045f * CARD_SIZE) + position.x,  (1.745f * CARD_SIZE) + position.y,     0.9644f, 0.9986f, (ivec3){ card_index, 0, 0 } },
        {  (1.000f * CARD_SIZE) + position.x,  (1.750f * CARD_SIZE) + position.y,     0.9444f, 1.0000f, (ivec3){ card_index, 0, 0 } }
    };
    array_buffer_reset_data(&renderer->card_positions_buffer, sizeof(vertices) * renderer->current_card_count, &vertices, sizeof(vertices));
    renderer->current_card_count++;
}
void card_renderer_draw(card_renderer* renderer) {
    shader_program_bind(&renderer->card_shader);

    texture_2d_bind(&renderer->cards_image, 0);
    vertex_array_bind(&renderer->card_vertex_array);
    vertex_array_draw(&renderer->card_vertex_array);   
    texture_2d_bind(NULL, 0);

    renderer->current_card_count = 0;

    array_buffer_reallocate(&renderer->card_positions_buffer, (sizeof(struct card_vertex) * 24) * 100, NULL);
}
void card_renderer_draw_plain(card_renderer* renderer) {
    vertex_array_bind(&renderer->card_vertex_array);
    vertex_array_draw(&renderer->card_vertex_array);   

    array_buffer_reallocate(&renderer->card_positions_buffer, (sizeof(struct card_vertex) * 24) * 100, NULL);

    renderer->current_card_count = 0;

}
void card_renderer_cleanup(card_renderer* renderer) {
    shader_program_delete(&renderer->card_shader);
    vertex_array_delete(&renderer->card_vertex_array);
    texture_2d_delete(&renderer->cards_image);
}