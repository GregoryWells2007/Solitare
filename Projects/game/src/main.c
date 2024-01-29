#include "stdio.h"
#include "engine.h"

struct triangle_vertex {
    float x, y;
    float u, v;
};

int main(int argc, char** argv) {
    engine_init();

    window_manager win_manager = window_manager_create();
    
    window main_window = window_create();
    window_manager_set_main_window(&win_manager, &main_window);

    window_data* main_window_data = window_get_data(&main_window); 
    window_data_set_name(main_window_data, "Main Window\0");
    window_data_set_size(main_window_data, (int2){ 1280, 720 });
    window_update_data(&main_window);

    window_properties* main_window_properties = window_get_properties(&main_window); // imma add some properties later
    window_properties_set_resizable(main_window_properties, false);
    window_properties_set_maximized(main_window_properties, false);
    window_properties_set_decorated(main_window_properties, true);
    window_update_properties(&main_window);

    window_open(&main_window);

    struct triangle_vertex vertices[24] = {
        { -1.000f,  1.750f, 0.0f, 0.0f },
        { -1.045f,  1.745f, 0.0f, 0.0f },
        { -1.075f,  1.735f, 0.0f, 0.0f },
        { -1.110f,  1.700f, 0.0f, 0.0f },
        { -1.120f,  1.670f, 0.0f, 0.0f },
        { -1.125f,  1.625f, 0.0f, 0.0f },
        
        { -1.125f, -1.625f, 0.0f, 0.0f },
        { -1.120f, -1.670f, 0.0f, 0.0f },
        { -1.110f, -1.700f, 0.0f, 0.0f },
        { -1.075f, -1.735f, 0.0f, 0.0f },
        { -1.045f, -1.745f, 0.0f, 0.0f },
        { -1.009f, -1.750f, 0.0f, 0.0f },

        {  1.000f, -1.750f, 0.0f, 0.0f },
        {  1.045f, -1.745f, 0.0f, 0.0f },
        {  1.075f, -1.735f, 0.0f, 0.0f },
        {  1.110f, -1.700f, 0.0f, 0.0f },
        {  1.120f, -1.670f, 0.0f, 0.0f },
        {  1.125f, -1.625f, 0.0f, 0.0f },

        {  1.125f,  1.625f, 0.0f, 0.0f },
        {  1.120f,  1.670f, 0.0f, 0.0f },
        {  1.110f,  1.700f, 0.0f, 0.0f },
        {  1.075f,  1.735f, 0.0f, 0.0f },
        {  1.045f,  1.745f, 0.0f, 0.0f },
        {  1.000f,  1.750f, 0.0f, 0.0f }
    };
    for (int i = 0; i < 24; i++) {
        vertices[i].x = vertices[i].x / 4.0f;
        vertices[i].y = vertices[i].y / 4.0f;

        vertices[i].x *= 0.9;
        vertices[i].y *= 1.6;
    }
    triangle triangles[22] = {
        { 0,  1, 22 },
        { 0, 23, 22 },

        { 1, 2, 21 },
        { 1, 22, 21 },

        { 2, 3, 20 },
        { 2, 21, 20 },

        { 3, 4, 19 },
        { 3, 20, 19 },

        { 4, 5, 18 },
        { 4, 19, 18 },

        { 5, 6, 17 },
        { 5, 18, 17 },

        { 6, 7, 16 },
        { 6, 17, 16 },

        { 7, 8, 15 },
        { 7, 16, 15 },

        { 8, 9, 14 },
        { 8, 15, 14 },

        { 9, 10, 13 },
        { 9, 14, 13 },

        { 10, 11, 12 },
        { 10, 13, 12 },
    };

    vertex_array triangle = vertex_array_create();

    array_buffer triangle_positions_buffer = array_buffer_create(); 
    array_buffer_set_data(&triangle_positions_buffer, vertices);
    array_buffer_set_vertex_count(&triangle_positions_buffer, 24);
    array_buffer_set_draw_type(&triangle_positions_buffer, static_draw);   

    vertex_attribute positions_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&triangle_positions_buffer, &positions_attribute);

    vertex_attribute uv_attribute = (vertex_attribute){ vertex_attribute_type_float, 2 };
    array_buffer_add_attribute(&triangle_positions_buffer, &uv_attribute);

    index_buffer triangle_index_buffer = index_buffer_create();
    index_buffer_set_data(&triangle_index_buffer, triangles);
    index_buffer_set_triangle_count(&triangle_index_buffer, 22);
    index_buffer_set_draw_type(&triangle_index_buffer, static_draw); 

    vertex_array_add_array_buffer(&triangle, &triangle_positions_buffer);
    vertex_array_set_index_buffer(&triangle, &triangle_index_buffer);

    vertex_array_build(&triangle);
    
    char* vertex_shader_src = ""
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec2 position;\n"
    "layout(location = 1) in vec2 uv;\n"
    "\n"
    "void main(void) {\n"
    "   gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n"
    ;

    char* fragment_shader_src = ""
    "#version 330 core\n"
    "\n"
    "out vec4 color;\n"
    "\n"
    "void main(void) {\n"
    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n"
    ;

    shader_program triangle_shader = shader_program_create();

    shader_stage triangle_vertex_shader = shader_stage_create();
    shader_stage_set_type(&triangle_vertex_shader, vertex_shader);
    shader_stage_set_source(&triangle_vertex_shader, vertex_shader_src);
    
    shader_stage triangle_fragment_shader = shader_stage_create();
    shader_stage_set_type(&triangle_fragment_shader, fragment_shader);
    shader_stage_set_source(&triangle_fragment_shader, fragment_shader_src);
    
    shader_program_set_stage(&triangle_shader, &triangle_vertex_shader);
    shader_program_set_stage(&triangle_shader, &triangle_fragment_shader);

    shader_program_build(&triangle_shader);

    clear_screen_data screen_clear = clear_screen_data_create(); 
    clear_screen_data_enable_layer(&screen_clear, color_layer);
    clear_screen_data_set_screen_color(&screen_clear, (color){ 150, 150, 150, 1.0f });

    while (window_is_open(&main_window)) {        
        clear_screen(&screen_clear);

        vertex_array_bind(&triangle);
        vertex_array_draw(&triangle);

        window_manager_update(&win_manager);
    }
    
    clear_screen_data_delete(&screen_clear);
    vertex_array_delete(&triangle);
    shader_program_delete(&triangle_shader);

    window_manager_delete(&win_manager);
    return 0;
}