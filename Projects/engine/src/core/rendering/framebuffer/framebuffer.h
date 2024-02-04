#pragma once
#include "engine_api.h"
#include "framebuffer_attachment.h"

typedef struct framebuffer {
    framebuffer_attachment** attachments;
    int attachment_count;
} framebuffer;

HEADER_DEF framebuffer framebuffer_create() {
    framebuffer new_framebuffer = (framebuffer){ };
    new_framebuffer.attachments = NULL;
    new_framebuffer.attachment_count = 0;
    return new_framebuffer;
}

HEADER_DEF void framebuffer_add_attachment(framebuffer* buffer, framebuffer_attachment* attachment) {
    buffer->attachments = realloc(buffer->attachments, sizeof(framebuffer_attachment) * (buffer->attachment_count + 1));
    buffer->attachments[buffer->attachment_count] = attachment;
    buffer->attachment_count++;
}

HEADER_DEF void framebuffer_build(framebuffer* buffer) {

}

HEADER_DEF void framebuffer_bind(framebuffer* buffer) {

}

HEADER_DEF void framebuffer_delete(framebuffer* buffer) {

}