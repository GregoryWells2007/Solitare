#pragma once
#include "engine_api.h"
#include "src/types/vector2.h"
#include "src/types/vector3.h"
#include "src/types/matrix4.h"

typedef struct transform2d {
    vector2 position;
    float rotation;
    vector2 scale;

    matrix4 mat;
} transform2d;

typedef struct transform3d {
    vector3 position;
    vector3 rotation;
    vector3 scale;

    matrix4 mat;
} transform3d;