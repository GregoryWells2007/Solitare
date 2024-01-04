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
    trans->matrix = glms_translate(glms_mat4_identity(), (vec3s){trans->position.x, trans->position.y, 0.0f});
    trans->matrix = glms_rotate(trans->matrix, glm_rad(trans->rotation), (vec3s){0.0f, 0.0f, 1.0f});
    trans->matrix = glms_scale(trans->matrix, (vec3s){trans->scale.x, trans->scale.y, 1.0f});
}