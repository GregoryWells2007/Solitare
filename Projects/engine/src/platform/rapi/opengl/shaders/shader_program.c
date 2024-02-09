#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "glad/glad.h"
#include "src/core/rendering/shaders/shader_program.h"
#include "src/types/matrix4.h"

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

struct platform_shader_uniform {
    unsigned uniformID;
};

void platform_upload_uniform_matrix4(unsigned int uniformID, void* data) {
    matrix4 value = *((matrix4*)data);
    glUniformMatrix4fv(uniformID, 1, GL_FALSE, (const GLfloat *) &value.values);
}
void platform_upload_uniform_matrix3(unsigned int uniformID, void* data) {
    printf("MATRIX3 uploading not supported\n");
} 
void platform_upload_uniform_int1(unsigned int uniformID, void* data) {
    int value = *((int*)data);
    glUniform1i(uniformID, value);
}
void platform_upload_uniform_int2(unsigned int uniformID, void* data) {
    printf("INT2 uploading not supported\n");
}
void platform_upload_uniform_int3(unsigned int uniformID, void* data) {
    printf("INT3 uploading not supported\n");
}
void platform_upload_uniform_int4(unsigned int uniformID, void* data) {
    printf("INT4 uploading not supported\n");
}
void platform_upload_uniform_uint1(unsigned int uniformID, void* data) {
    printf("UINT1 uploading not supported\n");
}
void platform_upload_uniform_uint2(unsigned int uniformID, void* data) {
    printf("UINT2 uploading not supported\n");
}
void platform_upload_uniform_uint3(unsigned int uniformID, void* data) {
    printf("UINT3 uploading not supported\n");
}
void platform_upload_uniform_uint4(unsigned int uniformID, void* data) {
    printf("UINT4 uploading not supported\n");
}
void platform_upload_uniform_float1(unsigned int uniformID, void* data) {
    printf("FLOAT1 uploading not supported\n");
}
void platform_upload_uniform_float2(unsigned int uniformID, void* data) {
    printf("FLOAT2 uploading not supported\n");
}
void platform_upload_uniform_float3(unsigned int uniformID, void* data) {
    printf("FLOAT3 uploading not supported\n");
}
void platform_upload_uniform_float4(unsigned int uniformID, void* data) {
    printf("FLOAT4 uploading not supported\n");
}

void platform_shader_uniform_set(shader_program* program, shader_uniform* uniform) {
    if (uniform->platform_shader_uniform == NULL) {
        uniform->platform_shader_uniform = malloc(sizeof(struct platform_shader_uniform));
        uniform->platform_shader_uniform->uniformID = glGetUniformLocation(program->platform_shader_program->rendererID, uniform->name);
    }

    unsigned int uniformID = uniform->platform_shader_uniform->uniformID;

    switch (uniform->type) {
    case uniform_matrix4: platform_upload_uniform_matrix4(uniformID, uniform->data); return; 
    case uniform_matrix3: platform_upload_uniform_matrix3(uniformID, uniform->data); return;  
    case uniform_int1: platform_upload_uniform_int1(uniformID, uniform->data); return;  
    case uniform_int2: platform_upload_uniform_int2(uniformID, uniform->data); return;  
    case uniform_int3: platform_upload_uniform_int3(uniformID, uniform->data); return;  
    case uniform_int4: platform_upload_uniform_int4(uniformID, uniform->data); return; 
    case uniform_uint1: platform_upload_uniform_uint1(uniformID, uniform->data); return;  
    case uniform_uint2: platform_upload_uniform_uint2(uniformID, uniform->data); return;  
    case uniform_uint3: platform_upload_uniform_uint3(uniformID, uniform->data); return;  
    case uniform_uint4: platform_upload_uniform_uint4(uniformID, uniform->data); return; 
    case uniform_float1: platform_upload_uniform_float1(uniformID, uniform->data); return;  
    case uniform_float2: platform_upload_uniform_float2(uniformID, uniform->data); return;  
    case uniform_float3: platform_upload_uniform_float3(uniformID, uniform->data); return;  
    case uniform_float4: platform_upload_uniform_float4(uniformID, uniform->data); return;     
    }
}

#endif