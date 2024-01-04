#pragma once

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