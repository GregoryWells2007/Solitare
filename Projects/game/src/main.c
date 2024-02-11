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

    framebuffer screen_framebuffer = framebuffer_create();

    // create a screen texture

    texture_2d color_texture = texture_2d_create();
    texture_2d_set_parameter(&color_texture, texture_2d_magnification_filter, texture_2d_filter_linear);
    texture_2d_set_parameter(&color_texture, texture_2d_minification_filter, texture_2d_filter_linear);

    texture_2d_set_parameter(&color_texture, texture_2d_wrap_x, texture_2d_wrap_repeat);
    texture_2d_set_parameter(&color_texture, texture_2d_wrap_y, texture_2d_wrap_repeat);

    texture_2d_set_width(&color_texture, 1280);
    texture_2d_set_height(&color_texture, 720);

    texture_2d_set_color_mode(&color_texture, RGBA);

    texture_2d_build(&color_texture);

    framebuffer_attachment framebuffer_color_attachment = framebuffer_attachment_create();
    framebuffer_attachment_set_data_type(&framebuffer_color_attachment, framebuffer_data_type_texture_2d);
    framebuffer_attachment_set_attachment_type(&framebuffer_color_attachment, color_attachment_0);
    framebuffer_attachment_set_data(&framebuffer_color_attachment, &color_texture);
    framebuffer_add_attachment(&screen_framebuffer, &framebuffer_color_attachment);

    renderbuffer depth_stencil_texture = renderbuffer_create();
    renderbuffer_set_width(&depth_stencil_texture, 1280);
    renderbuffer_set_height(&depth_stencil_texture, 720);
    renderbuffer_set_color_mode(&depth_stencil_texture, DEPTHSTENCIL);   

    renderbuffer_build(&depth_stencil_texture);

    framebuffer_attachment framebuffer_depth_stencil_attachment = framebuffer_attachment_create();
    framebuffer_attachment_set_data_type(&framebuffer_depth_stencil_attachment, framebuffer_data_type_renderbuffer);
    framebuffer_attachment_set_attachment_type(&framebuffer_depth_stencil_attachment, depth_stencil_attachment);
    framebuffer_attachment_set_data(&framebuffer_depth_stencil_attachment, &depth_stencil_texture);
    framebuffer_add_attachment(&screen_framebuffer, &framebuffer_depth_stencil_attachment);

    framebuffer_build(&screen_framebuffer);

    struct triangle_vertex vertices[24] = {
        { -1.000f,  1.750f,     0.0556f, 1.0000f },
        { -1.045f,  1.745f,     0.0356f, 0.9986f },
        { -1.075f,  1.735f,     0.0222f, 0.9957f },
        { -1.110f,  1.700f,     0.0067f, 0.9857f },
        { -1.120f,  1.670f,     0.0022f, 0.9771f },
        { -1.125f,  1.625f,     0.0000f, 0.9643f },
        
        { -1.125f, -1.625f,     0.0000f, 0.0357f },
        { -1.120f, -1.670f,     0.0022f, 0.0223f },
        { -1.110f, -1.700f,     0.0067f, 0.0143f },
        { -1.075f, -1.735f,     0.0222f, 0.0043f },
        { -1.045f, -1.745f,     0.0356f, 0.0014f },
        { -1.009f, -1.750f,     0.0556f, 0.0000f },

        {  1.000f, -1.750f,     0.9444f, 0.0000f },
        {  1.045f, -1.745f,     0.9644f, 0.0014f },
        {  1.075f, -1.735f,     0.9778f, 0.0043f },
        {  1.110f, -1.700f,     0.9933f, 0.0143f },
        {  1.120f, -1.670f,     0.9978f, 0.0223f },
        {  1.125f, -1.625f,     1.0000f, 0.0357f },

        {  1.125f,  1.625f,     1.0000f, 0.9643f },
        {  1.120f,  1.670f,     0.9978f, 0.9771f },
        {  1.110f,  1.700f,     0.9933f, 0.9857f },
        {  1.075f,  1.735f,     0.9778f, 0.9957f },
        {  1.045f,  1.745f,     0.9644f, 0.9986f },
        {  1.000f,  1.750f,     0.9444f, 1.0000f }
    };
    for (int i = 0; i < 24; i++) {
        vertices[i].x = vertices[i].x * 60.0f;
        vertices[i].y = vertices[i].y * 60.0f;
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

    file vertex_shader_file = file_load_from_path("../res/shaders/card_shader/card_shader_vertex.glsl");
    file fragment_shader_file = file_load_from_path("../res/shaders/card_shader/card_shader_fragment.glsl");

    shader_program triangle_shader = shader_program_create();

    shader_stage triangle_vertex_shader = shader_stage_create();
    shader_stage_set_type(&triangle_vertex_shader, vertex_shader);
    shader_stage_set_source(&triangle_vertex_shader, file_get_data(&vertex_shader_file));
    
    shader_stage triangle_fragment_shader = shader_stage_create();
    shader_stage_set_type(&triangle_fragment_shader, fragment_shader);
    shader_stage_set_source(&triangle_fragment_shader, file_get_data(&fragment_shader_file));
    
    shader_program_set_stage(&triangle_shader, &triangle_vertex_shader);
    shader_program_set_stage(&triangle_shader, &triangle_fragment_shader);

    shader_program_build(&triangle_shader);

    camera game_camera = camera_create();
    camera_set_bounds(&game_camera, -640.0f, 640.0f, 360.0f, -360.0f);
    camera_set_position(&game_camera, (vector2){0.0f, 0.0f});
    camera_set_rotation(&game_camera, 0.0f);

    int card_index = 10;
    int mouse_over = false;
    int card_held = false;
    shader_uniform card_index_uniform = (shader_uniform){ &card_index, "u_card_index", uniform_int1 };
    shader_uniform mouse_over_uniform = (shader_uniform){ &mouse_over, "mouse_over", uniform_int1 };
    shader_uniform card_held_uniform = (shader_uniform){ &card_held, "card_held", uniform_int1 };

    transform2d test_transform = transform2d_create();
    transform2d_set_position(&test_transform, (vector2){ 100, 0 });

    shader_uniform camera_view_matrix = (shader_uniform){ &game_camera.camera_matrix, "camera_matrix", uniform_matrix4 };
    shader_uniform transform_matrix = (shader_uniform){ &test_transform.mat, "transform_matrix", uniform_matrix4 };

    shader_program_bind(&triangle_shader);
    shader_program_set_uniform(&triangle_shader, &card_index_uniform);
    shader_program_set_uniform(&triangle_shader, &mouse_over_uniform);
    shader_program_set_uniform(&triangle_shader, &card_held_uniform);
    shader_program_set_uniform(&triangle_shader, &camera_view_matrix);
    shader_program_set_uniform(&triangle_shader, &transform_matrix);
    shader_program_bind(NULL);

    texture_2d cards_image = texture_2d_create();
    texture_2d_set_parameter(&cards_image, texture_2d_magnification_filter, texture_2d_filter_nearest);
    texture_2d_set_parameter(&cards_image, texture_2d_minification_filter, texture_2d_filter_nearest);

    texture_2d_set_parameter(&cards_image, texture_2d_wrap_x, texture_2d_wrap_repeat);
    texture_2d_set_parameter(&cards_image, texture_2d_wrap_y, texture_2d_wrap_repeat);

    texture_file cards_texture_file = texture_file_load_from_path("../res/images/Cards.png");
    texture_2d_set_width(&cards_image, cards_texture_file.width);
    texture_2d_set_height(&cards_image, cards_texture_file.height);

    texture_2d_set_color_mode(&cards_image, RGBA);
    texture_2d_set_data(&cards_image, cards_texture_file.pixel_data);

    texture_2d_build(&cards_image);

    clear_screen_data screen_clear = clear_screen_data_create(); 
    clear_screen_data_enable_layer(&screen_clear, color_layer);
    clear_screen_data_set_screen_color(&screen_clear, (color){ 150, 150, 150, 1.0f });

    while (window_is_open(&main_window)) {      
        framebuffer_bind(&screen_framebuffer);
        clear_screen(&screen_clear);

        texture_2d_bind(&cards_image, 0);
        shader_program_bind(&triangle_shader);

        vertex_array_bind(&triangle);
        vertex_array_draw(&triangle);

        framebuffer_bind(NULL);
        texture_2d_bind(&color_texture, 0);

        window_manager_update(&win_manager);
    }
    
    clear_screen_data_delete(&screen_clear);
    
    texture_2d_delete(&color_texture);
    renderbuffer_delete(&depth_stencil_texture);
    framebuffer_delete(&screen_framebuffer);
    
    vertex_array_delete(&triangle);
    shader_program_delete(&triangle_shader);
    texture_2d_delete(&cards_image);

    window_manager_delete(&win_manager);
    return 0;
}