#pragma once
#include "engine_api.h"

#include "output_buffer_data.h"
#include "output_buffer_attachment.h"

typedef struct output_buffer {
    output_buffer_data data;

    output_buffer_attachment** output_buffer_attachments;
    int output_buffer_attachment_count;
} output_buffer;

HEADER_DEF output_buffer output_buffer_create() { 
    output_buffer new_buffer = (output_buffer){ }; 
    new_buffer.data = (output_buffer_data){};

    new_buffer.output_buffer_attachments = NULL;
    new_buffer.output_buffer_attachment_count = 0;

    return new_buffer;
}
HEADER_DEF output_buffer_data* output_buffer_get_properties(output_buffer* buffer) { return &buffer->data; }
HEADER_DEF void output_buffer_add_attachment(output_buffer* buffer, output_buffer_attachment* attachment) {
    buffer->output_buffer_attachments = realloc(buffer->output_buffer_attachments, buffer->output_buffer_attachment_count + 1);
    buffer->output_buffer_attachments[buffer->output_buffer_attachment_count] = attachment;
    buffer->output_buffer_attachment_count++;
}

void output_buffer_initilize() {
    // just do the rapi stuff
}