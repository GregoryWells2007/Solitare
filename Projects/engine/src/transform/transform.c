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
    mat4s pos_matrix = glms_translate(glms_mat4_identity(), (vec3s){trans->position.x, trans->position.y, 0.0f});
    mat4s rot_matrix = glms_rotate(glms_mat4_identity(), glm_rad(trans->rotation), (vec3s){0.0f, 0.0f, 1.0f});
    mat4s scl_matrix = glms_scale(glms_mat4_identity(), (vec3s){trans->scale.x, trans->scale.y, 1.0f});

    mat4s transform_matrix = glms_mat4_mul(glms_mat4_mul(pos_matrix, rot_matrix), scl_matrix);
    trans->matrix = transform_matrix;
}