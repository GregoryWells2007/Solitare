#define NO_DEF_CLGM_CONFLICT
#include "camera.h"

void camera_gen_matrix(camera* cam) {
    cam->cameraMatrix = matrix4_orthographic(cam->left, cam->right, cam->top, cam->bottom, cam->front, cam->back);
}