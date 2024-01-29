#pragma once
#include "engine_api.h"
#include "string.h"

typedef enum shader_stage_type {
    no_stage,

    vertex_shader, fragment_shader, 
    geometry_shader, 
    compute_shader, 
    tessellation_evaluation_shader, tessellation_control_shader
} shader_stage_type;

typedef struct shader_stage {
    shader_stage_type stage_type;
    char* shader_source;
} shader_stage;

HEADER_DEF shader_stage shader_stage_create() {
    shader_stage new_shader_stage = (shader_stage){ };
    new_shader_stage.stage_type = no_stage;
    new_shader_stage.shader_source = NULL;
    return new_shader_stage;
}

HEADER_DEF void shader_stage_set_type(shader_stage* stage, shader_stage_type stage_type) { stage->stage_type = stage_type; }
HEADER_DEF void shader_stage_set_source(shader_stage* stage, char* source) { stage->shader_source = strdup(source); }