#pragma once
#include "engine_api.h"
#include "src/types/color.h"

typedef enum screen_layer {
    color_layer
} screen_layer; 

typedef struct clear_screen_data clear_screen_data;
void platform_set_screen_color(color col);
void platform_clear_screen(screen_layer* layers, int count);

 
typedef struct clear_screen_data {
    color screen_color;

    // i need other regions later
    screen_layer* layers_enabled;
    int layer_count;
} clear_screen_data;


HEADER_DEF clear_screen_data clear_screen_data_create() {
    clear_screen_data new_data;
    new_data.layers_enabled = NULL;
    new_data.layer_count = 0;

    new_data.screen_color = (color){ 0, 0, 0, 1.0f };
    return new_data;
}

HEADER_DEF void clear_screen_data_enable_layer(clear_screen_data* data, screen_layer layer) {
    data->layers_enabled = realloc(data->layers_enabled, data->layer_count + 1);
    data->layers_enabled[data->layer_count] = layer;
    data->layer_count++;
}

HEADER_DEF void clear_screen_data_set_screen_color(clear_screen_data* data, color new_color) {
    data->screen_color = new_color;
    platform_set_screen_color(new_color);
}

HEADER_DEF void clear_screen(clear_screen_data* data) {
    platform_clear_screen(data->layers_enabled, data->layer_count);
}

HEADER_DEF void clear_screen_data_delete(clear_screen_data* data) {
    free(data->layers_enabled);
}