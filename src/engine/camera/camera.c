#include "camera.h"

void set_camera_bounds(camera* cam, float left, float right, float top, float bottom) {
    cam->left = left;
    cam->right = right;
    cam->top = top;
    cam->bottom = bottom;
    gen_cam_matrix(cam);
}

void set_camera_position(camera* cam, vector2 position) {
    cam->position = position;
    gen_cam_matrix(cam);
}

void set_camera_rotation(camera* cam, float rotation) {
    cam->rotation = rotation;
    gen_cam_matrix(cam);
}

void gen_cam_matrix(camera* cam) {
    //cam->cameraMatrix = glms_mat4_identity();
    cam->cameraMatrix = glms_ortho(cam->left, cam->right, cam->bottom, cam->top, -0.1f, 1000.0f);
}