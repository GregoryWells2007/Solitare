#include "camera.h"

void set_camera_bounds(camera* cam, float left, float right, float top, float bottom) {
    
    gen_cam_matrix(cam);
}

void set_camera_position(camera* cam, vector2 position) {

    gen_cam_matrix(cam);
}

void set_camera_rotation(camera* cam, float rotation) {
    
    gen_cam_matrix(cam);
}

void gen_cam_matrix(camera* cam) {
    cam->cameraMatrix = glms_mat4_identity();
}