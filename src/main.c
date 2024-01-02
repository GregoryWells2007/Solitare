#include "stdio.h"
#include "mesh/mesh.h"
#include "window/window.h"

int main(int argc, char** argv) {
    init_windows();

    window_data main_window_data = { 1280, 720, "Solitare AI\0" };
    window main_window = create_window(main_window_data);

    init_opengl();


    // float card_mesh_positions[size] = {
    //     -1.0f, 1.75f,
    //      1.0f, 1.75f,
    //      1.0f, 1.625f,
         
    //      1.0f, 1.625f,
    //     -1.0f, 1.625f,
    //     -1.0f, 1.75f, 
    // };

    // for (int i = 0; i < size; i++) {
    //     card_mesh_positions[i] = card_mesh_positions[i] / 2.0f; 
    // }

    float card_mesh_positions[8] = {
        -1.0f, 1.75f,
        
    };

    int card_index_positions[6] = {
        0, 1, 2,
        0, 3, 1
    };


    mesh_data card_mesh_data = { 
        card_mesh_positions, 8,
        card_index_positions, 6
    };
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