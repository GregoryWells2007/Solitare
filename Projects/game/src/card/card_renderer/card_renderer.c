#include "card_renderer.h"

void card_renderer_init_shaders(card_renderer* renderer) {
    file vertex_shader_file = file_load_from_path("../res/shaders/card_shader/card_shader_vertex.glsl");
    file fragment_shader_file = file_load_from_path("../res/shaders/card_shader/card_shader_fragment.glsl");

    renderer->card_shader = shader_program_create();

    shader_stage triangle_vertex_shader = shader_stage_create();
    shader_stage_set_type(&triangle_vertex_shader, vertex_shader);
    shader_stage_set_source(&triangle_vertex_shader, file_get_data(&vertex_shader_file));
    
    shader_stage triangle_fragment_shader = shader_stage_create();
    shader_stage_set_type(&triangle_fragment_shader, fragment_shader);
    shader_stage_set_source(&triangle_fragment_shader, file_get_data(&fragment_shader_file));
    
    shader_program_set_stage(&renderer->card_shader, &triangle_vertex_shader);
    shader_program_set_stage(&renderer->card_shader, &triangle_fragment_shader);

    shader_program_build(&renderer->card_shader);

    // imma move this later
    camera game_camera = camera_create();
    camera_set_bounds(&game_camera, -640.0f, 640.0f, 360.0f, -360.0f);
    camera_set_position(&game_camera, (vector2){0.0f, 0.0f});
    camera_set_rotation(&game_camera, 0.0f);

    int card_index = 10;
    int mouse_over = false;
    int card_held = false;
    shader_uniform card_index_uniform = (shader_uniform){ &card_index, "u_card_index", uniform_int1 };
    shader_uniform mouse_over_uniform = (shader_uniform){ &mouse_over, "mouse_over", uniform_int1 };
    shader_uniform card_held_uniform = (shader_uniform){ &card_held, "card_held", uniform_int1 };

    transform2d test_transform = transform2d_create();
    transform2d_set_position(&test_transform, (vector2){ 100, 0 });
    transform2d_set_rotation(&test_transform, 30.5f);
    transform2d_set_scale(&test_transform, (vector2){ 60.0, 60.0 });

    shader_uniform camera_view_matrix = (shader_uniform){ &game_camera.camera_matrix, "camera_matrix", uniform_matrix4 };
    shader_uniform transform_matrix = (shader_uniform){ &test_transform.mat, "transform_matrix", uniform_matrix4 };

    shader_program_bind(&renderer->card_shader);
    shader_program_set_uniform(&renderer->card_shader, &card_index_uniform);
    shader_program_set_uniform(&renderer->card_shader, &mouse_over_uniform);
    shader_program_set_uniform(&renderer->card_shader, &card_held_uniform);
    shader_program_set_uniform(&renderer->card_shader, &camera_view_matrix);
    shader_program_set_uniform(&renderer->card_shader, &transform_matrix);
    shader_program_bind(NULL);
}

void card_renderer_init(card_renderer* renderer) {
    card_renderer_init_shaders(renderer);
}
void card_renderer_draw_card(card_renderer* renderer, transform2d position) {
    shader_program_bind(&renderer->card_shader);
}
void card_renderer_cleanup(card_renderer* renderer) {
    shader_program_delete(&renderer->card_shader);
}