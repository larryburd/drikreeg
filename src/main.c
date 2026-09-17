#include "./ifaces/display.h"

int main() {
    struct GameState* gs = game_init();

    if (display_init() != 0) {
        puts("ERROR INITIALIZING DISPLAY");
    }

    if(display_render_board(gs) != 0) {
        puts("ERROR RENDERING BOARD");
    }

    getch();
    display_cleanup();
    return 0;
}
