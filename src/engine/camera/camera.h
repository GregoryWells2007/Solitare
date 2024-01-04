#pragma once
#include "cglm/struct.h"
#include "engine/types/multi2.h"

typedef struct camera {
    float left, right, top, bottom;
    vector2 position;
    float rotation;

    mat4s cameraMatrix;
} camera;

void set_camera_bounds(camera* cam, float left, float right, float top, float bottom);
void set_camera_position(camera* cam, vector2 position);
void set_camera_rotation(camera* cam, float rotation);

void gen_cam_matrix(camera* cam);