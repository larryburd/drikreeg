#include <ncurses.h>
#include "../ifaces/display.h"
#include "../ifaces/game_state.h"

/* Initialize the ncurses display library */
int display_init() {
    /* Minimum screen size needed */
    const int X_MIN = 80;
    const int Y_MIN = 24;

    int max_x, max_y;

    initscr();

    /* Check that we have enough screen realestate */
    getmaxyx(stdscr, max_y, max_x);
    if (max_x < X_MIN || max_y < Y_MIN) {
        printf("Screen area is too small.  Ensure there is %d x %d columns and rows, then try again", X_MIN, Y_MIN);

        return -1;
    }

    noecho();
    cbreak();
    start_color();
    curs_set(0);
    init_pair(PLAYER_ONE, COLOR_RED, COLOR_BLACK);  // Player one colors
    init_pair(PLAYER_TWO, COLOR_BLUE, COLOR_BLACK); // Player two colors
    return 0;
}

int display_cleanup() {
    endwin();
    return 0;
}

int display_render_board(struct GameState* gs) {
    const int SCREENBUFFER_X = 2;
    const int SCREENBUFFER_Y = 2;
    const int boardWidth = gs->boardMax_X * 2;

    for (int y = SCREENBUFFER_Y; y < SCREENBUFFER_Y + gs->boardMax_Y; ++y) {
        for (int x = SCREENBUFFER_X; x < SCREENBUFFER_X + boardWidth; x+=2) {
            char symbol = pieceSymbols[3]; // Default to empty square
            
            // Check if any piece is at this board position
            for (int i = 0; i < 6; ++i) {
                if (gs->pieces[i] != NULL && 
                    gs->pieces[i]->x * 2 + SCREENBUFFER_X == x && 
                    gs->pieces[i]->y + SCREENBUFFER_Y == y) {
                    symbol = gs->pieces[i]->icon;
                    break; // Found piece, stop checking
                }
            }
            
            mvaddch(y, x, symbol); // Draw either piece or empty square
        }
    }
    return 0;
}
int display_render_status(struct GameState* gs) {

    return 0;
}

int display_render_message(const char*) {

    return 0;
}

int display_refresh() {

    return 0;
}
