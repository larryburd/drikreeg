#include <string.h>
#include <stdio.h>
#include "../ifaces/messages.h"
#include "../ifaces/game_state.h"

/* implements a formatted message for a valid move int msg */
void moveMsg(char* msg, int msgSize, int currPlayer, struct Piece* piece, int to_x, int to_y) {
    char player[20];

    if (currPlayer == PLAYER_ONE) {
        strncpy(player, "Player One", sizeof(player) - 1);
    } else {
        strncpy(player, "Player Two", sizeof(player) - 1);
    }

    snprintf(msg, msgSize, "%s moved their %c from (%d, %d) to (%d, %d).", player, piece->icon, piece->x, piece->y, to_x, to_y);
    
    return;
}
