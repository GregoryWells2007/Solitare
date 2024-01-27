#include "stdio.h"
#include "engine.h"

struct triangle_vertex {
    float x, y;
};

int main(int argc, char** argv) {
    engine_init();

    window_manager win_manager = window_manager_create();
    
    window main_window = window_create();
    window_manager_set_main_window(&win_manager, &main_window);

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

    struct triangle_vertex vertices[3] = {
        { -0.5f, -0.5f },
        {  0.0f,  0.5f },
        {  0.5f, -0.5f }
    };

    triangle triangles[1] = {
        { 0, 1, 2 }
    };

    vertex_array triangle = vertex_array_create();

    array_buffer triangle_positions_buffer = array_buffer_create(); 
    array_buffer_set_data(&triangle_positions_buffer, vertices, 3);
    array_buffer_set_draw_type(&triangle_positions_buffer, static_draw);   

    vertex_attribute positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&triangle_positions_buffer, &positions_attribute);

    index_buffer triangle_index_buffer = index_buffer_create();
    index_buffer_set_data(&triangle_index_buffer, triangles);
    index_buffer_set_draw_type(&triangle_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&triangle, &triangle_positions_buffer);
    vertex_array_set_index_buffer(&triangle, &triangle_index_buffer);

    vertex_array_build(&triangle);
    
    while (window_is_open(&main_window)) {
        window_manager_update(&win_manager);
    }
     
    vertex_array_delete(&triangle);

    window_close(&main_window);
}