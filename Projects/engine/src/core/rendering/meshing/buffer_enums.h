#pragma once
#include "engine_api.h"

// i need more draw types but imma little lazy soooooooo this is it
typedef enum buffer_draw_type {
    none,
    static_draw, dynamic_draw
} buffer_draw_type;

// only floats for now bud
typedef enum vertex_attribute_type {
    vertex_attribute_type_float
} vertex_attribute_type;

HEADER_DEF size_t get_size_of_type(vertex_attribute_type type) {
    switch (type) {
    case vertex_attribute_type_float: return sizeof(float); 
    }
    return sizeof(float);
}