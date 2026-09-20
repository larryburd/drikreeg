#include "./ifaces/display.h"
#include "./ifaces/messages.h"

int main() {
    struct GameState* gs = game_init();
    struct Move* move;
    char msg[256];

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

    /* TEST DATA */
    /* Player One Moves */
    move = createMove(gs->pieces[0]->x, gs->pieces[0]->y, 7, 2, 0, 0);
    if (isMoveLegal(gs, move) == 0) {
        display_animate_piece_move(gs, gs->pieces[0], 7, 2);
        moveMsg(msg, sizeof(msg), gs->currPlayer, move, gs);
        display_render_message(msg);
        changeTurns(gs);
    } else {
        display_render_message("Illegal move!");
    }
    display_refresh(gs);

    getch();

    /* Player Two Moves */
    move = createMove(gs->pieces[4]->x, gs->pieces[4]->y, 7, 10, 0, 4);
    if (isMoveLegal(gs, move) == 0) {
        display_animate_piece_move(gs, gs->pieces[4], 7, 10);
        moveMsg(msg, sizeof(msg), gs->currPlayer, move, gs);
        display_render_message(msg);
        changeTurns(gs);
    } else {
        display_render_message("Illegal move!");
    }
    display_refresh(gs);
    getch();

    /* END TEST DATA */
    display_cleanup();
    return 0;
}
