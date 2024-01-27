#pragma once

typedef struct vector3 {
    union {
        struct { int x, y, z; };    
        struct { int a, b, c; };     
    };
} vector3;

typedef vector3 float3;
typedef vector3 vec3;

typedef vector3 Vector3;
typedef vector3 Float3;
typedef vector3 Vec3;

typedef vector3 triangle;