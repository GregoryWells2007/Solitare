#pragma once

typedef struct vector2i {
    union {
        struct { int x, y; };    
        struct { int a, b; };     
    };
} vector2i;

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

/////// -------------- //

typedef vector2i int2;
typedef vector2i ivec2;

typedef vector2i vector2int;

typedef vector2i Vector2int;
typedef vector2i Int2;
typedef vector2i IVec2;