#include "stdio.h"
#include "mesh/mesh.h"
#include "window/window.h"


int main(int argc, char** argv) {
    init_windows();

    window_data main_window_data = { 1280, 720, "Solitare AI\0" };
    window main_window = create_window(main_window_data);

    init_opengl();

    float card_mesh_positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f 
    };

    mesh_data card_mesh_data = { card_mesh_positions, 6 };
    mesh card_mesh = create_mesh(card_mesh_data);

    color window_color = { 38.0f, 162.0f, 105.0f, 1.0f };

    while (isOpen(&main_window)) {  
        clear_window(&main_window, window_color);

        draw_mesh(&card_mesh);
        draw_window(&main_window);
        
        update_windows();
    }

    close_windows();
    return 0;
}