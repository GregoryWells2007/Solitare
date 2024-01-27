#pragma once

typedef struct array_buffer {

} array_buffer;

array_buffer array_buffer_create() {
    array_buffer new_array_buffer = (array_buffer){ };
    return new_array_buffer;
}