#pragma once
#include "src/core/rendering/meshing/vertex_array.h"

typedef struct screen_renderer {
    vertex_array screen_vertex_array;

    vertex_attribute screen_positions_attribute;

    array_buffer screen_array_buffer;
    index_buffer screen_index_buffer;
} screen_renderer;

void screen_renderder_init(screen_renderer* renderer);
void screen_renderder_draw(screen_renderer* renderer);