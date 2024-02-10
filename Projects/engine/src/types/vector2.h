#pragma once
#include "engine_api.h"

typedef struct vector2f {
    union {
        struct { float x, y; };    
        struct { float a, b; };     
    };
} vector2f;

typedef vector2f float2;
typedef vector2f vec2;

typedef vector2f vector2;

typedef vector2f Vector2;
typedef vector2f Float2;
typedef vector2f Vec2;

HEADER_DEF bool vector2f_equals(vector2f v1, vector2f v2) { return (v1.x == v2.x) && (v1.y == v2.y); }

/////// -------------- //

typedef struct vector2i {
    union {
        struct { int x, y; };    
        struct { int a, b; };     
    };
} vector2i;

typedef vector2i int2;
typedef vector2i ivec2;

typedef vector2i vector2int;

typedef vector2i Vector2int;
typedef vector2i Int2;
typedef vector2i IVec2;

HEADER_DEF bool vector2i_equals(vector2i v1, vector2i v2) { return (v1.x == v2.x) && (v1.y == v2.y); }