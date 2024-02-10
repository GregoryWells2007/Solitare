#pragma once

#include "engine_api.h"
#include "src/types/vector2.h"
#include "src/types/matrix4.h"

typedef struct camera {
    float left, right, top, bottom;
    float front, back;
    float rotation;
    vector2 position;
    
    matrix4 camera_matrix;
} camera;

HEADER_DEF void camera_gen_matrix(camera* cam) {
    cam->camera_matrix = matrix4_orthographic(cam->left, cam->right, cam->top, cam->bottom, cam->front, cam->back);
}

HEADER_DEF camera camera_create() {
    camera new_camera = (camera){ };
    new_camera.left = 1;
    new_camera.right = -1;
    new_camera.top = 1;
    new_camera.bottom = -1;

    new_camera.front = -0.1f;
    new_camera.back = 1000.0f;

    new_camera.position = (vector2){ 0, 0 };
    new_camera.rotation = 0;

    new_camera.camera_matrix = (matrix4){};
    camera_gen_matrix(&new_camera);

    return new_camera;
}

HEADER_DEF void camera_set_bounds(camera* cam, float left, float right, float top, float bottom) {
    cam->left = left;
    cam->right = right;
    cam->top = top;
    cam->bottom = bottom;
    camera_gen_matrix(cam);
}
HEADER_DEF void camera_set_front(camera* cam, float front) {
    cam->front = front;
    camera_gen_matrix(cam);
}
HEADER_DEF void camera_set_back(camera* cam, float back) {
    cam->back = back;
    camera_gen_matrix(cam);
}
HEADER_DEF void camera_set_position(camera* cam, vector2 position) {
    cam->position = position;
    camera_gen_matrix(cam);
}
HEADER_DEF void camera_set_rotation(camera* cam, float rotation) {
    cam->rotation = 0;
    camera_gen_matrix(cam);
}