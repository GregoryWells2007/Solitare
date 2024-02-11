#pragma once
#include "engine_api.h"
#include "math.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

typedef struct matrix4 {
    float values[4][4];
} matrix4;

typedef matrix4 matrix4x4;

typedef matrix4 mat4x4;
typedef matrix4 mat4;

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

HEADER_DEF matrix4 matrix4_orthographic(float left, float right, float top, float bottom, float front, float near) {
    matrix4 new_matrix4 = matrix4_identity();

    new_matrix4.values[0][0] = 2.0f / (right - left);
    new_matrix4.values[0][3] = (right + left) / (right - left);

    new_matrix4.values[1][1] = 2.0f / (top - bottom);
    new_matrix4.values[1][3] = (top + bottom) / (top - bottom);

    new_matrix4.values[2][2] = -2.0f / (front - near);
    new_matrix4.values[2][3] = -1 * ((front + near) / (front - near));

    return new_matrix4;
}

HEADER_DEF matrix4 matrix4_translate(vector3 amt) {
    matrix4 new_matrix4 = matrix4_identity();

    new_matrix4.values[3][0] = amt.x;
    new_matrix4.values[3][1] = amt.y;
    new_matrix4.values[3][2] = amt.z;

    return new_matrix4;
}   

HEADER_DEF matrix4 matrix4_rotate_x(float amount) {
    matrix4 new_matrix4 = matrix4_identity();
    
    new_matrix4.values[1][1] = cos(amount);
    new_matrix4.values[1][2] = -sin(amount);
    new_matrix4.values[2][1] = sin(amount);
    new_matrix4.values[2][2] = cos(amount);

    return new_matrix4;
}

HEADER_DEF matrix4 matrix4_rotate_y(float amount) {
    matrix4 new_matrix4 = matrix4_identity();
    
    new_matrix4.values[0][0] = cos(amount);
    new_matrix4.values[0][2] = sin(amount);
    new_matrix4.values[2][0] = -sin(amount);
    new_matrix4.values[2][2] = cos(amount);

    return new_matrix4;
}

HEADER_DEF matrix4 matrix4_rotate_z(float amount) {
    matrix4 new_matrix4 = matrix4_identity();
    
    new_matrix4.values[0][0] = cos(amount);
    new_matrix4.values[0][1] = -sin(amount);
    new_matrix4.values[1][0] = sin(amount);
    new_matrix4.values[1][1] = cos(amount);

    return new_matrix4;
}

HEADER_DEF matrix4 matrix4_scale(vector3 amount) {
    matrix4 new_matrix4 = matrix4_identity();
    new_matrix4.values[0][0] = amount.x;
    new_matrix4.values[0][0] = amount.y;
    new_matrix4.values[0][0] = amount.z;
    return new_matrix4;
}