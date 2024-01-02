#pragma once

typedef struct multi4 {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };

        struct {
            float r;
            float g;
            float b;
            float a;
        };
    };
} multi4;

typedef multi4 color;
typedef multi4 vector4;
typedef multi4 quaternion;