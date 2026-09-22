#include <string.h>
#include <stdio.h>
#include "../ifaces/messages.h"
#include "../ifaces/game_state.h"
#include "../ifaces/move.h"

/* implements a formatted message for a valid move int msg */
void moveMsg(char* msg, int msgSize, int currPlayer, struct Move* move, struct GameState* gs) {
    char player[20];
    char icon = gs->pieces[move->pieceIndex]->icon;

    if (currPlayer == PLAYER_ONE) {
        strncpy(player, "Player One", sizeof(player) - 1);
    } else {
        strncpy(player, "Player Two", sizeof(player) - 1);
    }

    snprintf(msg, msgSize, "%s moved their %c from (%d, %d) to (%d, %d).", player, icon, move->fromX, move->fromY, move->toX, move->toY);
    addActionHist(gs, msg);
}
