#pragma once
#include "engine_api.h"
#include "shader_stage.h"

typedef struct shader_program {
    shader_stage** stages;
    int stage_count;
} shader_program;

HEADER_DEF shader_program shader_program_create() {
    shader_program new_shader_program = (shader_program){ };
    new_shader_program.stages = NULL;
    new_shader_program.stage_count;
    return new_shader_program;
}

HEADER_DEF void shader_program_set_stage(shader_program* program, shader_stage* stage) {
    program->stages = realloc(program->stages, program->stage_count + 1);
    program->stages[program->stage_count] = stage;
    program->stage_count++;
}