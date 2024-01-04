#include "stdio.h"
#include "mesh/mesh.h"
#include "window/window.h"
#include "shader/shader.h"
#include "transform/transform.h"

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
        // Vertex            // UV cords
        -1.000f,  1.750f,    0.0556f, 0.0000f, // 0.0f, 0.0f, // 0
        -1.045f,  1.745f,    0.0356f, 0.0014f, // 0.0f, 0.0f, // 1
        -1.075f,  1.735f,    0.0222f, 0.0043f, // 0.0f, 0.0f, // 2
        -1.110f,  1.700f,    0.0067f, 0.0143f, // 0.0f, 0.0f, // 3
        -1.120f,  1.670f,    0.0022f, 0.0223f, // 0.0f, 0.0f, // 4
        -1.125f,  1.625f,    0.0000f, 0.0357f, // 0.0f, 0.0f, // 5

        -1.125f, -1.625f,    0.0000f, 0.9643f, // 0.0f, 1.0f, // 6
        -1.120f, -1.670f,    0.0022f, 0.9771f, // 0.0f, 1.0f, // 7
        -1.110f, -1.700f,    0.0067f, 0.9857f, // 0.0f, 1.0f, // 8
        -1.075f, -1.735f,    0.0222f, 0.9957f, // 0.0f, 1.0f, // 9
        -1.045f, -1.745f,    0.0356f, 0.9986f, // 0.0f, 1.0f, // 10
        -1.009f, -1.750f,    0.0556f, 1.0000f, // 0.0f, 1.0f, // 11

         1.000f, -1.750f,    0.9444f, 1.0000f, // 1.0f, 1.0f, // 12
         1.045f, -1.745f,    0.9644f, 0.9986f, // 1.0f, 1.0f, // 13
         1.075f, -1.735f,    0.9778f, 0.9957f, // 1.0f, 1.0f, // 14
         1.110f, -1.700f,    0.9933f, 0.9857f, // 1.0f, 1.0f, // 15
         1.120f, -1.670f,    0.9978f, 0.9771f, // 1.0f, 1.0f, // 16
         1.125f, -1.625f,    1.0000f, 0.9643f, // 1.0f, 1.0f, // 17

         1.125f,  1.625f,    1.0000f, 0.0357f, // 1.0f, 0.0f, // 18
         1.120f,  1.670f,    0.9978f, 0.0223f, // 1.0f, 0.0f, // 19
         1.110f,  1.700f,    0.9933f, 0.0143f, // 1.0f, 0.0f, // 20
         1.075f,  1.735f,    0.9778f, 0.0043f, // 1.0f, 0.0f, // 21
         1.045f,  1.745f,    0.9644f, 0.0014f, // 1.0f, 0.0f, // 22
         1.000f,  1.750f,    0.9444f, 0.0000f, // 1.0f, 0.0f  // 23
    };

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
        card_mesh_positions, 96,
        card_index_positions, 60
    };
    transform card_transform;
    vector2 card_position = { 0.0f, 0.0f };
    float card_rotation = 0.0f;
    vector2 card_scale = { 0.0f, 1.0f };
    set_transform_pos(&card_transform, card_position);
    set_transform_rot(&card_transform, card_rotation);
    set_transform_scl(&card_transform, card_scale);

    mesh card_mesh = create_mesh(card_mesh_data);
    color window_color = { 38.0f, 162.0f, 105.0f, 1.0f };

    shader_data data = load_shader_data_from_file("../res/shaders/card_shader/card_shader_vertex.glsl", "../res/shaders/card_shader/card_shader_fragment.glsl");
    shader card_shader = create_shader(data);

    shader_uniform card_transform_uniform = { &card_transform.matrix, matrix4, "transformMatrix\0" };

    while (isOpen(&main_window)) {  
        clear_window(&main_window, window_color);

        set_shader_uniform(&card_shader, &card_transform_uniform);

        bind_shader(&card_shader);
        draw_mesh(&card_mesh);

        draw_window(&main_window);
        update_windows();
    }

    close_windows();
    return 0;
}