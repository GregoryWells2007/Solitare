#pragma once
#include "engine_api.h"
#include "shader_stage.h"

typedef struct shader_program shader_program;
struct platform_shader_program;
void platform_shader_program_init(shader_program* program);
void platform_shader_program_create(shader_program* program);
void platform_shader_program_delete(shader_program* program);

typedef struct shader_program {
    shader_stage** stages;
    int stage_count;

    struct platform_shader_program* platform_shader_program;
} shader_program;

HEADER_DEF shader_program shader_program_create() {
    shader_program new_shader_program = (shader_program){ };
    new_shader_program.stages = NULL;
    new_shader_program.stage_count;
    new_shader_program.platform_shader_program = NULL;
    return new_shader_program;
}

HEADER_DEF void shader_program_set_stage(shader_program* program, shader_stage* stage) {
    if (stage->stage_type == no_stage) {
        printf("you forgot to set the shader stage type\n");
        return;
    }

    program->stages = realloc(program->stages, program->stage_count + 1);
    program->stages[program->stage_count] = stage;
    program->stage_count++;
}

HEADER_DEF void shader_program_build(shader_program* program) {
    platform_shader_program_init(program);

    for (int i = 0; i < program->stage_count; i++)
        shader_stage_build(program->stages[i]);

    platform_shader_program_create(program);
}

HEADER_DEF void shader_program_delete(shader_program* program) {
    for (int i = 0; i < program->stage_count; i++) {
        shader_stage_delete(program->stages[i]);
    }

    free(program->stages);

    platform_shader_program_delete(program);
    free(program->platform_shader_program);
}