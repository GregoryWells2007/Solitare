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

    // create transform for card

    card new_card = { (card_data){ five, hearts }, (vector2){ 0.0f, 0.0f }, 40.0f };

    while (isOpen(&main_window)) {  
        clear_window(&main_window, (color){ 38.0f, 162.0f, 105.0f, 1.0f });

        start_card_renderer_frame(&renderer);
        draw_card(&renderer, new_card);

        draw_window(&main_window);
        update_windows();
    }

    close_windows();
    return 0;
}