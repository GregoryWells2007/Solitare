#pragma once

#include <cglm/struct.h>

#include "src/types/multi2.h"

typedef struct transform {
    vector2 position;
    float rotation;
    vector2 scale;
    
    mat4s matrix;
} transform;

void set_transform_pos(struct transform* trans, vector2 new_pos);
void set_transform_rot(struct transform* trans, float new_rot);
void set_transform_scl(struct transform* trans, vector2 new_scl);

void calculate_transform_mat(struct transform* trans);