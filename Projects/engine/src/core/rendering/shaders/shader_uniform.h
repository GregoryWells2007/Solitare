#pragma once
#include "engine_api.h"

typedef enum shader_uniform_type {
    uniform_matrix4, uniform_matrix3, 
    uniform_int1, uniform_int2, uniform_int3, uniform_int4,
    uniform_uint1, uniform_uint2, uniform_uint3, uniform_uint4,
    uniform_float1, uniform_float2, uniform_float3, uniform_float4
} shader_uniform_type;

typedef struct shader_uniform {
    void* data;
    char* name;
    shader_uniform_type type;
} shader_uniform;