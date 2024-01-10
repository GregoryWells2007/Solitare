#include "stdio.h"
#include "engine.h"

int main(int argc, char** argv) {
    init_windows();
    window_data main_window_data = { 1280, 720, "Solitare\0" };
    window main_window = create_window(main_window_data);
    init_opengl();

    

    while (isOpen(&main_window)) {
        main_window.input->mouse_clicked = false;  
        update_windows();
        if (main_window.input->mouse_down && mouse_can_be_clicked) {
            main_window.input->mouse_clicked = true;  
            mouse_can_be_clicked = false;
        }
        if (!main_window.input->mouse_down)
            mouse_can_be_clicked = true;

        clear_window(&main_window, (color){ 38.0f, 162.0f, 105.0f, 1.0f });

        // do rendering

        draw_window(&main_window);
    }

    close_windows();
    return 0;
}