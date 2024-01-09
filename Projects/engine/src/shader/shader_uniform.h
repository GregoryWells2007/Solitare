#pragma once

typedef enum shader_uniform_type {
    matrix4, int1, int2, int3, int4
} shader_uniform_type;

typedef struct shader_uniform {
    void* data;
    shader_uniform_type type;
    char* name;
} shader_uniform;