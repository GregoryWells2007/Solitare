#pragma once

typedef struct vector4i {
    union {
        struct { int x, y, z, w; };    
        struct { int a, b, c, d; };     
    };
} vector4i;

typedef struct vector4f {
    union {
        struct { float x, y, z, w; };    
        struct { float a, b, c, d; };     
    };
} vector4f;

typedef vector4f float4;
typedef vector4f vec4;

typedef vector4f vector4;

typedef vector4f Vector4;
typedef vector4f Float4;
typedef vector4f Vec4;

typedef vector4f quaternion;

/////// -------------- //

typedef vector4i int4;
typedef vector4i ivec4;

typedef vector4i vector4int;

typedef vector4i Vector4int;
typedef vector4i Int4;
typedef vector4i IVec4;