#pragma once
#include "engine.h"

// imma add some more stuff to this later like positions of the slots but im kinda lazy so it just has the image for now
typedef struct board {
    image board_image;
    
    vector2 board_spades_position;
    vector2 board_clubs_position;
    vector2 board_hearts_position;
    vector2 board_diamonds_position;

    vector2 board_cards_position_1;
    vector2 board_cards_position_2;
    vector2 board_cards_position_3;
    vector2 board_cards_position_4;
    vector2 board_cards_position_5;
    vector2 board_cards_position_6;
    vector2 board_cards_position_7;

    vector2 card_stack_position;
} board;

void create_background(board* board, char* path); 

