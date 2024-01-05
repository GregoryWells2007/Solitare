#include "card_renderer.h"

void card_renderer_create_mesh(card_renderer* renderer) {
    float card_mesh_positions[] = {
        // Vertex            // UV cords
        -1.000f,  1.750f,    0.0556f, 1.0000f, // 0.0f, 1.0f, // 0
        -1.045f,  1.745f,    0.0356f, 0.9986f, // 0.0f, 1.0f, // 1
        -1.075f,  1.735f,    0.0222f, 0.9957f, // 0.0f, 1.0f, // 2
        -1.110f,  1.700f,    0.0067f, 0.9857f, // 0.0f, 1.0f, // 3
        -1.120f,  1.670f,    0.0022f, 0.9771f, // 0.0f, 1.0f, // 4
        -1.125f,  1.625f,    0.0000f, 0.9643f, // 0.0f, 1.0f, // 5

        -1.125f, -1.625f,    0.0000f, 0.0357f, // 0.0f, 0.0f, // 6
        -1.120f, -1.670f,    0.0022f, 0.0223f, // 0.0f, 0.0f, // 7
        -1.110f, -1.700f,    0.0067f, 0.0143f, // 0.0f, 0.0f, // 8
        -1.075f, -1.735f,    0.0222f, 0.0043f, // 0.0f, 0.0f, // 9
        -1.045f, -1.745f,    0.0356f, 0.0014f, // 0.0f, 0.0f, // 10
        -1.009f, -1.750f,    0.0556f, 0.0000f, // 0.0f, 0.0f, // 11

         1.000f, -1.750f,    0.9444f, 0.0000f, // 1.0f, 0.0f, // 12
         1.045f, -1.745f,    0.9644f, 0.0014f, // 1.0f, 0.0f, // 13
         1.075f, -1.735f,    0.9778f, 0.0043f, // 1.0f, 0.0f, // 14
         1.110f, -1.700f,    0.9933f, 0.0143f, // 1.0f, 0.0f, // 15
         1.120f, -1.670f,    0.9978f, 0.0223f, // 1.0f, 0.0f, // 16
         1.125f, -1.625f,    1.0000f, 0.0357f, // 1.0f, 0.0f, // 17

         1.125f,  1.625f,    1.0000f, 0.9643f, // 1.0f, 1.0f, // 18
         1.120f,  1.670f,    0.9978f, 0.9771f, // 1.0f, 1.0f, // 19
         1.110f,  1.700f,    0.9933f, 0.9857f, // 1.0f, 1.0f, // 20
         1.075f,  1.735f,    0.9778f, 0.9957f, // 1.0f, 1.0f, // 21
         1.045f,  1.745f,    0.9644f, 0.9986f, // 1.0f, 1.0f, // 22
         1.000f,  1.750f,    0.9444f, 1.0000f, // 1.0f, 1.0f  // 23
    };

    int card_index_positions[] = {
        0,  1, 22,
        0, 23, 22,

        1, 2, 21,
        1, 22, 21,

        2, 3, 20,
        2, 21, 20,

        3, 4, 19,
        3, 20, 19,

        4, 5, 18,
        4, 19, 18,

        5, 6, 17,
        5, 18, 17,

        6, 7, 16,
        6, 17, 16,

        7, 8, 15,
        7, 16, 15,

        8, 9, 14,
        8, 15, 14,

        9, 10, 13,
        9, 14, 13,

        10, 11, 12,
        10, 13, 12,
    };


    mesh_data card_mesh_data = { 
        card_mesh_positions, 96,
        card_index_positions, 66
    };
    mesh card_mesh = create_mesh(card_mesh_data);

    renderer->card_mesh = card_mesh;
}

void card_renderer_create_shader(card_renderer* renderer) {
    shader_data data = load_shader_data_from_file("../res/shaders/card_shader/card_shader_vertex.glsl", "../res/shaders/card_shader/card_shader_fragment.glsl");
    shader card_shader = create_shader(data);
    renderer->card_shader = card_shader;
}

void card_renderer_create_camera(card_renderer* renderer) {
    camera game_camera;
    set_camera_bounds(&game_camera, -640.0f, 640.0f, 360.0f, -360.0f);
    set_camera_position(&game_camera, (vector2){0.0f, 0.0f});
    set_camera_rotation(&game_camera, 0.0f);
    renderer->card_camera = game_camera; 
}

void card_renderer_create_image(card_renderer* renderer) {
    image img = load_image_from_file("../res/images/Cards.png");
    renderer->card_image = img;
}

void init_card_renderer(card_renderer* renderer) {
    card_renderer_create_mesh(renderer);
    card_renderer_create_shader(renderer);
    card_renderer_create_camera(renderer);
    card_renderer_create_image(renderer);
}

void start_card_renderer_frame(card_renderer* renderer) {
    bind_shader(&renderer->card_shader);
    shader_uniform game_camera_uniform = { &renderer->card_camera.cameraMatrix, matrix4, "camera_matrix\0" };
    set_shader_uniform(&renderer->card_shader, &game_camera_uniform);
}


void draw_card(card_renderer* renderer, card* value) {
    bind_shader(&renderer->card_shader);
    bind_image(&renderer->card_image);

    transform card_transform;
    set_transform_pos(&card_transform, (vector2){ value->position.x, value->position.y });
    set_transform_rot(&card_transform, 0.0f);
    set_transform_scl(&card_transform, (vector2){ value->scale, value->scale });
    shader_uniform card_transform_uniform = { &card_transform.matrix, matrix4, "transform_matrix\0" };
    
    set_shader_uniform(&renderer->card_shader, &card_transform_uniform);
    
    int card_index_value = card_data_to_number(value->data);
    shader_uniform card_type_uniform = { &card_index_value, int1, "u_card_index" };
    set_shader_uniform(&renderer->card_shader, &card_type_uniform);

    int value_for_mouse_over = 0;
    if (value->mouse_over == true)
        value_for_mouse_over = 1;

    shader_uniform card_hovered_uniform = { &value_for_mouse_over, int1, "mouse_over" };
    set_shader_uniform(&renderer->card_shader, &card_hovered_uniform);

    draw_mesh(&renderer->card_mesh);
}