#pragma once
#include "src/core/rendering/meshing/vertex_array.h"
#include "src/core/rendering/shaders/shader_program.h"

typedef struct screen_renderer {
    vertex_array screen_vertex_array;

    vertex_attribute screen_positions_attribute;
    vertex_attribute screen_uvs_attribute;

    array_buffer screen_array_buffer;
    index_buffer screen_index_buffer;

    // shader stuff

    shader_program screen_shader;

    shader_stage screen_renderder_vertex_shader;
    shader_stage screen_renderer_fragment_shader;

    char* vertex_shader_src;
    char* fragment_shader_src;
} screen_renderer;

void screen_renderder_init(screen_renderer* renderer);
void screen_renderder_draw(screen_renderer* renderer);