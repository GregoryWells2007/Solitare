#pragma once
#include "src/core/rendering/meshing/vertex_array.h"
#include "src/core/rendering/shaders/shader_program.h"

struct screen_mesh {
    vertex_array screen_vertex_array;

    vertex_attribute screen_positions_attribute;
    vertex_attribute screen_uvs_attribute;

    array_buffer screen_array_buffer;
    index_buffer screen_index_buffer;
};

struct screen_shader {
    shader_program screen_shader;

    shader_stage screen_renderder_vertex_shader;
    shader_stage screen_renderer_fragment_shader;

    char* vertex_shader_src;
    char* fragment_shader_src;
};

struct screen_data {
    float vignette_power;
};

typedef struct screen_renderer {
    struct screen_mesh screen_mesh;
    struct screen_shader screen_shader;
} screen_renderer;

void screen_renderer_init(screen_renderer* renderer);
void screen_renderer_draw(screen_renderer* renderer);
void screen_renderer_delete(screen_renderer* renderer);