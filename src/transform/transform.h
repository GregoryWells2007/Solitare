#pragma once
#include <cglm/cglm.h>
#include <cglm/struct.h>
#include "cglm/mat4.h"
#include "types/multi2.h"

// this line exists because i can not stand not having syntax highlighting 

typedef struct transform {
    vector2 position;
    float rotation;
    vector2 scale;
    
    mat4s matrix;
} transform;

void set_transform_pos(transform* trans, vector2 new_pos);
void set_transform_rot(transform* trans, float new_rot);
void set_transform_scl(transform* trans, vector2 new_scl);

void calculate_transform_mat(transform* trans);