#include "./ifaces/display.h"

int main() {
    struct GameState* gs = game_init();

    if (display_init() != 0) {
        puts("ERROR INITIALIZING DISPLAY");
    }

    if(display_render_board(gs) != 0) {
        puts("ERROR RENDERING BOARD");
    }

    if(display_render_status(gs) != 0) {
        puts("ERROR RENDERING STATUS");
    }

    getch();

    display_animate_piece_move(gs, gs->pieces[0], 3, 3);
    changeTurns(gs);
    display_refresh(gs);

    getch();
    display_cleanup();
    return 0;
}
