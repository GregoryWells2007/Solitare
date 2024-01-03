#include "transform.h"

void set_transform_pos(transform* trans, vector2 new_pos) {
    trans->position = new_pos;
    calculate_transform_mat(trans);
}

void set_transform_rot(transform* trans, float new_rot) {
    trans->rotation = new_rot;
    calculate_transform_mat(trans);
}

void set_transform_scl(transform* trans, vector2 new_scl) {
    trans->scale = new_scl;
    calculate_transform_mat(trans);
}

void calculate_transform_mat(transform* trans) {
    trans->matrix = glms_mat4_identity();
}