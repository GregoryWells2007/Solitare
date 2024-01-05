#pragma once
#include "engine.h"

// imma add some more stuff to this later like positions of the slots but im kinda lazy so it just has the image for now
typedef struct board {
    image board_image;
} board;

void create_background(board* board, char* path); 

