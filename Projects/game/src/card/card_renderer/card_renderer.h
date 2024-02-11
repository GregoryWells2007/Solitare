#pragma once
#include "engine.h"

#define card_shader_data                    \
    shader_program card_shader;             \
                                            \
    shader_stage triangle_vertex_shader;    \
    shader_stage triangle_fragment_shader;  \
                                            \
    shader_uniform card_index_uniform;      \
    shader_uniform mouse_over_uniform;      \
    shader_uniform card_held_uniform;       \
                                            \
    shader_uniform camera_view_matrix;      \
    shader_uniform transform_matrix;        \

typedef struct card_renderer {
    card_shader_data;

    camera game_camera;
} card_renderer;

void card_renderer_init(card_renderer* renderer);
void card_renderer_draw_card(card_renderer* renderer, vector2 position, int card_index);
void card_renderer_cleanup(card_renderer* renderer);