#pragma once

typedef struct vector3i {
    union {
        struct { int x, y, z; };    
        struct { int a, b, c; };     
    };
} vector3i;

typedef struct vector3f {
    union {
        struct { float x, y, z; };    
        struct { float a, b, c; };     
    };
} vector3f;

typedef vector3f float3;
typedef vector3f vec3;

typedef vector3f vector3;

typedef vector3f Vector3;
typedef vector3f Float3;
typedef vector3f Vec3;

/////// -------------- //

typedef vector3i triangle;

typedef vector3i int3;
typedef vector3i ivec3;

typedef vector3i vector3int;

typedef vector3i Vector3int;
typedef vector3i Int3;
typedef vector3i IVec3;