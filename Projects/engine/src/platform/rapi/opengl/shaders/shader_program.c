#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "glad/glad.h"
#include "src/core/rendering/shaders/shader_program.h"

struct platform_shader_program {
    unsigned int rendererID;
};

void platform_shader_program_init(shader_program* program) {
    program->platform_shader_program = malloc(sizeof(struct platform_shader_program));
    program->platform_shader_program->rendererID = glCreateProgram();
}

void platform_shader_program_create(shader_program* program) {
    glLinkProgram(program->platform_shader_program->rendererID);
    glValidateProgram(program->platform_shader_program->rendererID);
}

void platform_shader_program_delete(shader_program* program) {
    glDeleteProgram(program->platform_shader_program->rendererID);
}

#endif