#include "stdio.h"
#include "engine.h"

#include "card/card.h"
#include "card/renderer/card_renderer.h"
#include "card/hover/card_hover.h"
#include "card/manager/card_manager.h"
#include "board/board.h"
#include "board/board_renderer/board_renderer.h"

int main(int argc, char** argv) {
    init_windows();
    window_data main_window_data = { 1280, 720, "Solitare AI\0" };
    window main_window = create_window(main_window_data);
    init_opengl();

    // create card renderer
    card_renderer card_renderer = {};
    init_card_renderer(&card_renderer);

    // create card manager
    card_hover hover = { main_window.input };
    card_manager manager = {};
    manager.hover = &hover;
    manager.renderer = &card_renderer;
    create_cards(&manager);


    // create background
    board game_board = {  };
    create_background(&game_board, "../res/images/Background.png\0");
    
    board_renderer board_renderer = {};
    init_board_renderer(&board_renderer);

    // create transform for card

    while (isOpen(&main_window)) {  
        clear_window(&main_window, (color){ 38.0f, 162.0f, 105.0f, 1.0f });

        draw_board(&board_renderer, &game_board);

        start_card_renderer_frame(&card_renderer);
        update_card_manager(&manager);
        // test_card_hover(&hover, &new_card);
        // draw_card(&card_renderer, &new_card);

        draw_window(&main_window);
        update_windows();
    }

    close_windows();
    return 0;
}