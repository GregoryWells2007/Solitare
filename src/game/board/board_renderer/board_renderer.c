#include "board_renderer.h"

void create_board_mesh(board_renderer* renderer) {
    float board_mesh_positions[] = {
        -1.0f,  1.0f,   0.0f, 1.0f,
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,   1.0f, 1.0f
    };

    int board_index_positions[] = {
        0, 1, 2,
        0, 3, 2 
    };

    mesh_data board_mesh_data = { 
        board_mesh_positions, 16,
        board_index_positions, 6
    };
    mesh board_mesh = create_mesh(board_mesh_data);
    renderer->board_mesh = board_mesh;
}

void create_board_shader(board_renderer* renderer) {
    shader_data data = load_shader_data_from_file("../res/shaders/background_shader/background_shader_vertex.glsl", "../res/shaders/background_shader/background_shader_fragment.glsl");
    shader board_shader = create_shader(data);
    renderer->board_shader = board_shader;
}

void init_board_renderer(board_renderer* renderer) {
    create_board_mesh(renderer);
    create_board_shader(renderer);
}

void draw_board(board_renderer* renderer, board* board) {
    bind_image(&board->board_image);

    bind_shader(&renderer->board_shader);
    draw_mesh(&renderer->board_mesh);
}