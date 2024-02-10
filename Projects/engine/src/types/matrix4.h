#pragma once
#include "engine_api.h"

typedef struct matrix4 {
    float values[4][4];
} matrix4;

typedef matrix4 matrix4x4;

typedef matrix4 mat4x4;
#ifndef NO_DEF_CLGM_CONFLICT
typedef matrix4 mat4;
#endif

HEADER_DEF matrix4 matrix4_identity() {
    matrix4 new_matrix4 = (matrix4) { };

    new_matrix4.values[0][0] = 1.0f;
    new_matrix4.values[0][1] = 0.0f;
    new_matrix4.values[0][2] = 0.0f;
    new_matrix4.values[0][3] = 0.0f;

    new_matrix4.values[1][0] = 0.0f;
    new_matrix4.values[1][1] = 1.0f;
    new_matrix4.values[1][2] = 0.0f;
    new_matrix4.values[1][3] = 0.0f;

    new_matrix4.values[2][0] = 0.0f;
    new_matrix4.values[2][1] = 0.0f;
    new_matrix4.values[2][2] = 1.0f;
    new_matrix4.values[2][3] = 0.0f;

    new_matrix4.values[3][0] = 0.0f;
    new_matrix4.values[3][1] = 0.0f;
    new_matrix4.values[3][2] = 0.0f;
    new_matrix4.values[3][3] = 1.0f;

    return new_matrix4;
}