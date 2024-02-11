#pragma once
#include "../board.h"
#include "engine.h"

#include "../../card/card_renderer/card_renderer.h"

#define board_shader_data                   \
    shader_program board_shader;            \
                                            \
    shader_stage board_vertex_shader;       \
    shader_stage board_fragment_shader;            

#define board_vertex_data                   \
    vertex_array board_vertex_array;        \
                                            \
    array_buffer board_positions_buffer;    \
    index_buffer board_index_buffer;         

#define board_uniforms                      \
    shader_uniform texture_index_uniform;   \
    shader_uniform board_mesh_uniform;      \
    shader_uniform transform_uniform;       \
    shader_uniform camera_uniform

typedef struct board_renderer {
    board_vertex_data;
    board_shader_data;
    board_uniforms;

    card_renderer* card_renderer;
} board_renderer;

void board_renderer_init(board_renderer* renderer);
void board_renderer_init_board(board_renderer* renderer, board* board);
void board_renderer_draw_board(board_renderer* renderer, board* board);
void board_renderer_cleanup(board_renderer* renderer);