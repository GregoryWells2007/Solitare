#include "stdio.h"
#include "engine.h"

#include "board/board_renderer/board_renderer.h"
#include "card/card_renderer/card_renderer.h"

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

    clear_screen_data screen_clear = clear_screen_data_create(); 
    clear_screen_data_enable_layer(&screen_clear, color_layer);
    clear_screen_data_set_screen_color(&screen_clear, (color){ 150, 150, 150, 1.0f });

    card_renderer card_renderer = {};
    card_renderer_init(&card_renderer);

    board_renderer board_renderer = {};
    board_renderer_init(&board_renderer);

    board new_board = {};
    new_board.background_image = "../res/images/background.png";
    new_board.areas_image = "../res/images/card_bases.png";
    board_renderer_init_board(&board_renderer, &new_board);

    while (window_is_open(&main_window)) {      
        framebuffer_bind(&screen_framebuffer);
        clear_screen(&screen_clear);

        board_renderer_draw_board(&board_renderer, &new_board);

        card_renderer_draw_card(&card_renderer, (vector2){ -100, 0 }, 0);
        card_renderer_draw_card(&card_renderer, (vector2){  100, 0 }, 52);

        framebuffer_bind(NULL);
        texture_2d_bind(&color_texture, 0);

        window_manager_update(&win_manager);
    }
    
    clear_screen_data_delete(&screen_clear);
    
    texture_2d_delete(&color_texture);
    renderbuffer_delete(&depth_stencil_texture);
    framebuffer_delete(&screen_framebuffer);
    
    board_renderer_cleanup(&board_renderer);
    card_renderer_cleanup(&card_renderer);

    window_manager_delete(&win_manager);
    return 0;
}