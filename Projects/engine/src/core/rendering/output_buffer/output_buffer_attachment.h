#pragma once
#include "engine_api.h"

typedef enum output_buffer_attachment_texture_format {
    RGBA8, DEPTH24STENCIL8
} output_buffer_attachment_texture_format;

typedef struct output_buffer_attachment {
    output_buffer_attachment_texture_format texture_format;
} output_buffer_attachment;

HEADER_DEF output_buffer_attachment output_buffer_attachment_create() { return (output_buffer_attachment){ }; }
HEADER_DEF void output_buffer_attachment_set_texture_format(output_buffer_attachment* attachment, output_buffer_attachment_texture_format new_format) { attachment->texture_format = new_format; }