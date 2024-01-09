#pragma once
#include "src/types/multi2.h"
#include "cglm/struct.h"


typedef struct camera {
    float left, right, top, bottom;
    vector2 position;
    float rotation;

    mat4s cameraMatrix;
} camera;

void set_camera_bounds(struct camera* cam, float left, float right, float top, float bottom);
void set_camera_position(struct camera* cam, vector2 position);
void set_camera_rotation(struct camera* cam, float rotation);

void gen_cam_matrix(struct camera* cam);