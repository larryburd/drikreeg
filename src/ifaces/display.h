#ifndef DISPLAY_H
#define DISPLAY_H

#define LINUX

#ifdef LINUX
    #include <ncurses.h>
#elif defined(_WIN32)
    // Windows headers will go here
#endif

#include "game_state.h"

// All display functions return 0 for success and -1 for error
int display_init();
int display_cleanup();
int display_render_board(struct GameState* gs);
int display_render_status(struct GameState* gs);
int display_render_message(const char*);
int display_animate_piece_move(struct GameState* gs, struct Piece* piece, int target_x, int target_y);
int display_refresh();

#endif
