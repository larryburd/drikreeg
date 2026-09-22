#include <stdio.h>
#include <stdlib.h>
#include "./ifaces/game_state.h"
#include "./ifaces/move.h"
#include "./ifaces/display.h"

int main() {
    struct GameState* gs = game_init();
    struct Move* move;

    if (display_init() != 0) {
        puts("ERROR INITIALIZING DISPLAY");
        return -1;
    }

    if(display_render_board(gs) != 0) {
        puts("ERROR RENDERING BOARD");
        return -1;
    }

    if(display_render_status(gs) != 0) {
        puts("ERROR RENDERING STATUS");
        return -1;
    }

    getch();

    /* TEST DATA */
    /* Player One Moves */
    move = createMove(gs->pieces[0], 7, 2, 0);
    movePiece(gs, move);
    getch();
    move = createMove(gs->pieces[4], 10, 10, MOVE);
    movePiece(gs, move);
    getch();

    /* END TEST DATA */
    display_cleanup();
    free(move);
    free(gs);
    return 0;
}
