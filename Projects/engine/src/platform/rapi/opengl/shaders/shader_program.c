#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "glad/glad.h"
#include "src/core/rendering/shaders/shader_program.h"

struct platform_shader_program {
    unsigned int rendererID;
};

// skethy should be replaces later but im a lazy little fuck
struct platform_shader_stage {
    unsigned int rendererID;
};

void platform_shader_program_init(shader_program* program) {
    program->platform_shader_program = malloc(sizeof(struct platform_shader_program));
    program->platform_shader_program->rendererID = glCreateProgram();
}

void platform_shader_program_create(shader_program* program) {
    for (int i = 0; i < program->stage_count; i++) {
        glAttachShader(program->platform_shader_program->rendererID, program->stages[i]->platform_shader_stage->rendererID);
    }

    glLinkProgram(program->platform_shader_program->rendererID);
    glValidateProgram(program->platform_shader_program->rendererID);

    glUseProgram(program->platform_shader_program->rendererID);
}

void platform_shader_program_delete(shader_program* program) {
    glDeleteProgram(program->platform_shader_program->rendererID);
}

void platform_shader_program_bind(shader_program* program) {
    if (!program)
        glUseProgram(0);
    else    
        glUseProgram(program->platform_shader_program->rendererID);
}

#endif