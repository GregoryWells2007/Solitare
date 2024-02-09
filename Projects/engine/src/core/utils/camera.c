#include <cglm/cglm.h>
#include <cglm/struct.h>

#define NO_DEF_CLGM_CONFLICT
#include "camera.h"

void camera_gen_matrix(camera* cam) {
    mat4s ortho_matrix = glms_ortho(cam->left, cam->right, cam->bottom, cam->top, cam->front, cam->back);

    cam->cameraMatrix.values[0][0] = ortho_matrix.m00;
    cam->cameraMatrix.values[1][0] = ortho_matrix.m10;
    cam->cameraMatrix.values[2][0] = ortho_matrix.m20;
    cam->cameraMatrix.values[3][0] = ortho_matrix.m30;

    cam->cameraMatrix.values[0][1] = ortho_matrix.m01;
    cam->cameraMatrix.values[1][1] = ortho_matrix.m11;
    cam->cameraMatrix.values[2][1] = ortho_matrix.m21;
    cam->cameraMatrix.values[3][1] = ortho_matrix.m31;

    cam->cameraMatrix.values[0][2] = ortho_matrix.m02;
    cam->cameraMatrix.values[1][2] = ortho_matrix.m12;
    cam->cameraMatrix.values[2][2] = ortho_matrix.m22;
    cam->cameraMatrix.values[3][2] = ortho_matrix.m32;

    cam->cameraMatrix.values[0][3] = ortho_matrix.m03;
    cam->cameraMatrix.values[1][3] = ortho_matrix.m13;
    cam->cameraMatrix.values[2][3] = ortho_matrix.m23;
    cam->cameraMatrix.values[3][3] = ortho_matrix.m33;
}