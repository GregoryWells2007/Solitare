#pragma once
#include "engine_api.h"
#include "../textures/texture_2d/texture_2d.h"

typedef enum framebuffer_attachment_type {
    color_attachment_0,
    depth_stencil_attachment,

    framebuffer_attachment_type_none
} framebuffer_attachment_type;

typedef enum framebuffer_data_type {
    framebuffer_data_type_renderbuffer,
    framebuffer_data_type_texture_2d,

    framebuffer_data_type_none
} framebuffer_data_type;

typedef struct framebuffer_attachment {
    void* data;
    framebuffer_attachment_type attachment_type;
    framebuffer_data_type data_type;
} framebuffer_attachment;

HEADER_DEF framebuffer_attachment framebuffer_attachment_create() {
    framebuffer_attachment new_framebuffer_attachment = (framebuffer_attachment){ };
    new_framebuffer_attachment.data = NULL;
    new_framebuffer_attachment.attachment_type = framebuffer_attachment_type_none;
    new_framebuffer_attachment.data_type = framebuffer_data_type_none;
    return new_framebuffer_attachment;
}

HEADER_DEF void framebuffer_attachment_set_data_type(framebuffer_attachment* attachment, framebuffer_data_type dat_type) { attachment->data_type = dat_type; }
HEADER_DEF void framebuffer_attachment_set_attachment_type(framebuffer_attachment* attachment, framebuffer_attachment_type attach_type) { attachment->attachment_type = attach_type; }
HEADER_DEF void framebuffer_attachment_set_data(framebuffer_attachment* attachment, void* data) { attachment->data = data; }