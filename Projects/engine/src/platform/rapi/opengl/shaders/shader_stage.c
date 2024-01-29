#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/shaders/shader_stage.h"
#include "glad/glad.h"
#include "string.h"

struct platform_shader_stage {
    unsigned int rendererID;
};

GLenum get_gl_shader_type(shader_stage_type type) {
    switch (type) {
    case vertex_shader: return GL_VERTEX_SHADER;
    case fragment_shader: return GL_FRAGMENT_SHADER;
    case geometry_shader: return GL_GEOMETRY_SHADER; 
    case compute_shader: return GL_COMPUTE_SHADER; 
    case tessellation_evaluation_shader: return GL_TESS_EVALUATION_SHADER;
    case tessellation_control_shader: return GL_TESS_CONTROL_SHADER;

    case no_stage: printf("not sure how you got this far in life and how you got past my rigourous checks but shits wrong mate you gotta check that out\n");
    }
}

const char* get_shader_type_string(shader_stage_type type) {
    switch (type) {
    case vertex_shader: return "GL_VERTEX_SHADER";
    case fragment_shader: return "GL_FRAGMENT_SHADER";
    case geometry_shader: return "GL_GEOMETRY_SHADER"; 
    case compute_shader: return "GL_COMPUTE_SHADER"; 
    case tessellation_evaluation_shader: return "GL_TESS_EVALUATION_SHADER";
    case tessellation_control_shader: return "GL_TESS_CONTROL_SHADER";

    case no_stage: return "FUCK YOU BITCH";
    }
}

void platform_shader_stage_build(shader_stage* stage) {

    int shader_length = strlen(stage->shader_source);

    unsigned int rendererID = glCreateShader(get_gl_shader_type(stage->stage_type));
    glShaderSource(rendererID, 1, (const GLchar *const *)&stage->shader_source, (const GLint *) &shader_length);
    glCompileShader(rendererID);

    int result = 0;
    glGetShaderiv(rendererID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glGetShaderiv(rendererID, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(rendererID, length, &length, message);
        printf("Failed to compile %s shader\n", get_shader_type_string(stage->stage_type));
        printf("Reason: {%s}", message);
    }

    stage->platform_shader_stage = malloc(sizeof(struct platform_shader_stage));
    stage->platform_shader_stage->rendererID = rendererID;
}

#endif