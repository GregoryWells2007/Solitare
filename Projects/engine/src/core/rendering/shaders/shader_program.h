#pragma once
#include "engine_api.h"
#include "shader_stage.h"

#include "shader_uniform.h"

typedef struct shader_program shader_program;
struct platform_shader_program;
void platform_shader_program_init(shader_program* program);
void platform_shader_program_create(shader_program* program);
void platform_shader_program_delete(shader_program* program);
void platform_shader_program_bind(shader_program* program);

void platform_shader_uniform_set(shader_program* program, shader_uniform* uniform);

typedef struct shader_program {
    shader_stage** stages;
    int stage_count;

    shader_uniform** uniforms;
    int uniform_count;

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

HEADER_DEF void shader_program_bind(shader_program* program) {
    platform_shader_program_bind(program);
}

HEADER_DEF void shader_program_build(shader_program* program) {
    platform_shader_program_init(program);

    for (int i = 0; i < program->stage_count; i++)
        shader_stage_build(program->stages[i]);

    platform_shader_program_create(program);
    shader_program_bind(NULL);
}

HEADER_DEF void shader_program_delete(shader_program* program) {
    for (int i = 0; i < program->stage_count; i++) {
        shader_stage_delete(program->stages[i]);
    }

    for (int i = 0; i < program->uniform_count; i++) {
        free(program->uniforms[i]->platform_shader_uniform);
    }

    free(program->stages);

    platform_shader_program_delete(program);
    free(program->platform_shader_program);
}

HEADER_DEF void shader_program_set_uniform(shader_program* program, shader_uniform* uniform) { 
    program->uniforms = realloc(program->uniforms, program->uniform_count + 1);
    program->uniforms[program->uniform_count] = uniform;
    program->uniform_count++;

    platform_shader_uniform_set(program, uniform);
}

HEADER_DEF void shader_program_update_uniforms(shader_program* program, shader_uniform* uniform) {
    for (int i = 0; i < program->uniform_count; i++) {
        platform_shader_uniform_set(program, program->uniforms[i]);
    }
}