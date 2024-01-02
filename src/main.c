#include "stdio.h"
#include "mesh/mesh.h"
#include "window/window.h"
#include "shader/shader.h"

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


    float card_mesh_positions[] = {
        -1.000f,  1.750f, // 0
        -1.045f,  1.745f, // 1
        -1.075f,  1.735f, // 2
        -1.110f,  1.700f, // 3
        -1.120f,  1.670f, // 4
        -1.125f,  1.625f, // 5
        -1.125f, -1.625f, // 6
        -1.120f, -1.670f, // 7
        -1.110f, -1.700f, // 8
        -1.075f, -1.735f, // 9
        -1.045f, -1.745f, // 10
        -1.009f, -1.750f, // 11
         1.000f, -1.750f, // 12
         1.045f, -1.745f, // 13
         1.075f, -1.735f, // 14
         1.110f, -1.700f, // 15
         1.120f, -1.670f, // 16
         1.125f, -1.625f, // 17
         1.125f,  1.625f, // 18
         1.120f,  1.670f, // 19
         1.110f,  1.700f, // 20
         1.075f,  1.735f, // 21
         1.045f,  1.745f, // 22
         1.000f,  1.750f  // 23
    };

    for (int i = 0; i < 48; i++) {
        card_mesh_positions[i] = card_mesh_positions[i] / 2.0f; 
    }

    int card_index_positions[] = {
        0,  1, 22,
        0, 23, 22,

        1, 2, 21,
        1, 22, 21,

        2, 3, 20,
        2, 21, 20,

        3, 4, 19,
        3, 20, 19,

        4, 5, 18,
        4, 19, 18,

        5, 6, 17,
        5, 18, 17,

        6, 7, 16,
        6, 17, 16,

        7, 8, 15,
        7, 16, 15,

        8, 9, 14,
        8, 15, 14,

        9, 10, 13,
        9, 14, 13,

        10, 11, 12,
        10, 13, 12,
    };


    mesh_data card_mesh_data = { 
        card_mesh_positions, 48,
        card_index_positions, 60
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