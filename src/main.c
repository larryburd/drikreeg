#include "./ifaces/display.h"
#include "./ifaces/messages.h"

int main() {
    struct GameState* gs = game_init();
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
    if (is_move_legal(gs, gs->pieces[0], 7, 2) == 0) {
        display_animate_piece_move(gs, gs->pieces[0], 3, 3);
        moveMsg(msg, sizeof(msg), gs->currPlayer, gs->pieces[0], 3, 3);
        display_render_message(msg);
        changeTurns(gs);
    } else {
        display_render_message("Illegal move!");
    }
    display_refresh(gs);

    getch();
    display_cleanup();
    return 0;
}
