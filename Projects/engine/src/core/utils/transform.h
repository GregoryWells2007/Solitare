#pragma once
#include "engine_api.h"
#include "mathf.h"
#include "src/types/vector2.h"
#include "src/types/vector3.h"
#include "src/types/matrix4.h"

typedef struct transform2d {
    vector2 last_position;
    float last_rotation;
    vector2 last_scale;

    vector2 position;
    float rotation;
    vector2 scale;

    matrix4 translation_mat;
    matrix4 rotation_mat;
    matrix4 scale_mat;

    matrix4 mat;
} transform2d;
HEADER_DEF matrix4 transform2d_get_matrix(transform2d* transform) { return transform->mat; }

HEADER_DEF void transform2d_gen_matrix(transform2d* transform) {
    bool changed = false;

    if (!vector2f_equals(transform->position, transform->last_position)) {
        vector3 pos = { transform->position.x, transform->position.y, 0.0f };
        transform->translation_mat = matrix4_translate(pos);
        changed = true;
    }

    if (transform->rotation != transform->last_rotation) {
        transform->rotation_mat = matrix4_rotate_z(radians(transform->rotation););
        changed = true;
    }

    if (!vector2f_equals(transform->scale, transform->last_scale)) {
        // regen scale mat
        changed = true;
    }

    if (changed) {
        transform->mat = transform->rotation_mat;
    }

    transform->last_position = transform->position;
    transform->last_rotation = transform->rotation;
    transform->last_scale = transform->scale;
}

HEADER_DEF transform2d transform2d_set_position(transform2d* transform, vector2f position) {
    transform->position = position;
    transform2d_gen_matrix(transform);
}

HEADER_DEF transform2d transform2d_set_rotation(transform2d* transform, float rotation) {
    transform->rotation = rotation;
    transform2d_gen_matrix(transform);
}

HEADER_DEF transform2d transform2d_create() {
    transform2d new_transform2d = (transform2d){ };
    
    new_transform2d.position = (vector2){ 0, 0 };
    new_transform2d.rotation = 0.0f;
    new_transform2d.scale = (vector2){ 1, 1 };

    new_transform2d.translation_mat = matrix4_identity();
    new_transform2d.rotation_mat = matrix4_identity();
    new_transform2d.scale_mat = matrix4_identity();
    new_transform2d.mat = matrix4_identity();

    transform2d_gen_matrix(&new_transform2d);

    return new_transform2d;
}

typedef struct transform3d {
    vector3 position;
    vector3 rotation;
    vector3 scale;

    matrix4 mat;
} transform3d;