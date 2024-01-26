#include "stdio.h"
#include "engine.h"

int main(int argc, char** argv) {
    engine_init();

    window main_window = window_create();

    window_data* main_window_data = window_get_data(&main_window); 
    window_data_set_name(main_window_data, "Main Window\0");
    window_data_set_size(main_window_data, (vector2){ 1280, 720 });
    window_update_data(&main_window);

    window_properties* main_window_properties = window_get_properties(&main_window); // imma add some properties later
    window_properties_set_resizable(main_window_properties, false);
    window_properties_set_maximized(main_window_properties, false);
    window_properties_set_decorated(main_window_properties, true);
    window_update_properties(&main_window);

    window_open(&main_window);

    output_buffer game_output_buffer = output_buffer_create();
    output_buffer_data* game_output_buffer_properties = output_buffer_get_properties(&game_output_buffer);
    output_buffer_data_set_size(game_output_buffer_properties, (vector2){ 1280, 720 });

    output_buffer_attachment color_attachment = output_buffer_attachment_create();
    output_buffer_attachment_set_texture_format(&color_attachment, RGBA8);

    output_buffer_attachment depth_stencil_attachment = output_buffer_attachment_create();
    output_buffer_attachment_set_texture_format(&depth_stencil_attachment, DEPTH24STENCIL8);

    output_buffer_add_attachment(&game_output_buffer, &color_attachment);
    output_buffer_add_attachment(&game_output_buffer, &depth_stencil_attachment);

    output_buffer_initilize(&game_output_buffer);

    while (window_is_open(&main_window)) {    
        window_update(&main_window);
    }
     
    window_close(&main_window);
}