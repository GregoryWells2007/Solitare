#pragma once

typedef struct vector2 {
    union {
        struct { int x, y; };    
        struct { int a, b; };     
    };
} vector2;

typedef vector2 float2;
typedef vector2 vec2;

typedef vector2 Vector2;
typedef vector2 Float2;
typedef vector2 Vec2;