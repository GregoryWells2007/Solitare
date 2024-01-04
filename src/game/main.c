#include "stdio.h"
#include "engine.h"

#include "card/card.h"
#include "card/renderer/card_renderer.h"

int main(int argc, char** argv) {
    init_windows();
    window_data main_window_data = { 1280, 720, "Solitare AI\0" };
    window main_window = create_window(main_window_data);
    init_opengl();


    card_renderer renderer = {};
    init_card_renderer(&renderer);

    // create test card
    card_data test_card_data = { five, hearts };
    printf("Card index: %i\n", card_data_to_number(test_card_data));

    // create transform for card
    transform card_transform;
    set_transform_pos(&card_transform, (vector2){ 0.0f, 0.0f });
    set_transform_rot(&card_transform, 0.0f);
    set_transform_scl(&card_transform, (vector2){ 4.0f, 4.0f });
    shader_uniform card_transform_uniform = { &card_transform.matrix, matrix4, "transform_matrix\0" };

    shader_uniform game_camera_uniform = { &renderer.card_camera.cameraMatrix, matrix4, "camera_matrix\0" };

    color window_color = { 38.0f, 162.0f, 105.0f, 1.0f };

    image img = load_image_from_file("../res/images/Cards.png");

    while (isOpen(&main_window)) {  
        clear_window(&main_window, window_color);

        set_shader_uniform(&renderer.card_shader, &card_transform_uniform);
        set_shader_uniform(&renderer.card_shader, &game_camera_uniform);

        bind_shader(&renderer.card_shader);
        draw_mesh(&renderer.card_mesh);

        draw_window(&main_window);
        update_windows();
    }

    close_windows();
    return 0;
}