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

void card_renderer_init(card_renderer* renderer) {
    card_renderer_create_camera(renderer);

    card_renderer_init_shaders(renderer);
    card_renderer_create_uniforms(renderer);
}
void card_renderer_draw_card(card_renderer* renderer, vector2 position, int card_index) {
    shader_program_bind(&renderer->card_shader);
}
void card_renderer_cleanup(card_renderer* renderer) {
    shader_program_delete(&renderer->card_shader);
}