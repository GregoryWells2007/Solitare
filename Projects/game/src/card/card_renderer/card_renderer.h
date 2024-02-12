#pragma once
#include "engine.h"

#define card_shader_data                    \
    shader_program card_shader;             \
                                            \
    shader_stage triangle_vertex_shader;    \
    shader_stage triangle_fragment_shader;  \
                                            \
    shader_uniform camera_view_matrix;      

#define card_vertex_data                    \
    vertex_array card_vertex_array;         \
                                            \
    array_buffer card_positions_buffer;     \
    index_buffer card_index_buffer;         
    
#define card_texture_data                   \
    texture_2d cards_image

typedef struct card_renderer {
    card_shader_data;
    card_vertex_data;
    card_texture_data;

    camera game_camera;
    int current_card_count;
} card_renderer;

void card_renderer_init(card_renderer* renderer);
void card_renderer_draw_card(card_renderer* renderer, vector2 position, int card_index);
void card_renderer_draw(card_renderer* renderer);
void card_renderer_draw_plain(card_renderer* renderer);
void card_renderer_cleanup(card_renderer* renderer);