#include "stdio.h"
#include "engine.h"

#include "card/card.h"
#include "card/renderer/card_renderer.h"
#include "card/hover/card_hover.h"
#include "card/manager/card_manager.h"
#include "board/board.h"
#include "board/board_renderer/board_renderer.h"

// if i ever want to print FPS
// #define PRINT_FPS 

void set_board_positions(board* board_to_set) {
    board_to_set->board_clubs_position = (vector2){ -565, 260 };
    board_to_set->board_spades_position = (vector2){ -466, 260 };
    board_to_set->board_hearts_position = (vector2){ -365, 260 };
    board_to_set->board_diamonds_position = (vector2){ -265, 260 };

    board_to_set->board_cards_position_1 = (vector2){ -565, 50 };
    board_to_set->board_cards_position_2 = (vector2){ -430, 50 };
    board_to_set->board_cards_position_3 = (vector2){ -289, 50 };
    board_to_set->board_cards_position_4 = (vector2){ -150, 50 };
    board_to_set->board_cards_position_5 = (vector2){  -15, 50 };
    board_to_set->board_cards_position_6 = (vector2){  125, 50 };
    board_to_set->board_cards_position_7 = (vector2){  265, 50 };

    board_to_set->card_stack_position = (vector2){ 565, 260 };
}

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
    init_card_manager(&manager);


    // create background
    board game_board = {  };
    create_background(&game_board, "../res/images/Background.png\0");
    set_board_positions(&game_board);

    manager.loaded_board = &game_board;
    create_cards(&manager);
    create_piles(&manager);

    board_renderer board_renderer = {};
    init_board_renderer(&board_renderer);

    // create transform for card

    bool mouse_can_be_clicked = false;

    float startTime = 0.0f, endTime = 0.0f, totalTime = 0.0f;
    int frameCount = 0;

    while (isOpen(&main_window)) {
        startTime = get_time();

        main_window.input->mouse_clicked = false;  
        update_windows();
        if (main_window.input->mouse_down && mouse_can_be_clicked) {
            main_window.input->mouse_clicked = true;  
            mouse_can_be_clicked = false;
        }
        if (!main_window.input->mouse_down)
            mouse_can_be_clicked = true;

        clear_window(&main_window, (color){ 38.0f, 162.0f, 105.0f, 1.0f });

        draw_board(&board_renderer, &game_board);

        start_card_renderer_frame(&card_renderer);
        update_card_manager(&manager);

        draw_window(&main_window);

        endTime = get_time();
        totalTime += (endTime - startTime);
        frameCount++;
        if (totalTime >= 1.0f) {
            #ifdef PRINT_FPS
            printf("FPS: %i\n", frameCount);
            #endif
            frameCount = 0;
            totalTime = 0;
        }
    }

    close_windows();
    return 0;
}