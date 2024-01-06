#pragma once
#include "math.h"

typedef struct multi2 {
    union {
        struct {
            float x;
            float y;

        };

        struct {
            float a;
            float b;
        };
    };
} multi2;

typedef multi2 vector2;
float get_distance(vector2 v1, vector2 v2);