#include "../ifaces/move.h"
#include "../ifaces/display.h"
#include "../ifaces/messages.h"
#include "../ifaces/game_state.h"
#include <stdlib.h>
#include <stdio.h>

struct Move* createMove(struct Piece* piece, int toX, int toY, enum ActionType action) {
    struct Move* move = malloc(sizeof(struct Move));
    move->fromX = piece->x;
    move->fromY = piece->y;
    move->toX   = toX;
    move->toY   = toY;
    move->action = action;
    move->pieceIndex = piece->index;

    return move;
}

/**
 * is_move_legal - Checks if a move is legal based on game rules.
 * 
 * @param gs: Pointer to the GameState
 * @param piece: Pointer to the piece being moved
 * @param target_x: X coordinate of the destination
 * @param target_y: Y coordinate of the destination
 * 
 * @return: 0 if move is legal, -1 if illegal
 * 
 * Checks:
 *   - Destination is within board bounds
 *   - Distance from current position doesn't exceed mvLimit (movement limit)
 *   - No other piece occupies the destination
 */
int isMoveLegal(struct GameState* gs, struct Move* move) {
    struct Piece* piece = gs->pieces[move->pieceIndex];

    /* Check if target is within board bounds */
    if (move->toX < 0 || move->toX >= gs->boardMax_X || 
        move->toY < 0 || move->toY >= gs->boardMax_Y) {
        return -1;  /* Out of bounds */
    }
    
    /* Calculate Manhattan distance (total squares to travel) */
    int distance = abs(move->fromX - move->toX) + abs(move->fromY - move->toY);
    
    /* Check if distance exceeds movement limit */
    if (distance > piece->mvLimit) {
        return -1;  /* Too far to move */
    }
    
    /* Check if another piece occupies the destination */
    for (int i = 0; i < 6; i++) {
        if (gs->pieces[i] != NULL && 
            gs->pieces[i] != piece &&  /* Don't check the piece against itself */
            gs->pieces[i]->x == move->toX && 
            gs->pieces[i]->y == move->toY) 
        {
            return -1;  /* Space occupied */
        }
    }
    
    return 0;  /* Move is legal */
}

char* actionToString(enum ActionType type) {
    static const char* actionStrings[] = {
        "Move",
        "Attack",
        "Heal",
    };

    if (type >= 0 && type < 3) {
        return actionStrings[type];
    }

    return "Unkown";
}

int movePiece(struct GameState* gs, struct Move* move) {
    char msg[256];

    if (isMoveLegal(gs, move) == 0) {
        display_animate_piece_move(gs, move);
        moveMsg(msg, sizeof(msg), gs->currPlayer, move, gs);
        display_render_message(msg);
        changeTurns(gs);
    } else {
        display_render_message("Illegal Move!");
    }

    display_refresh(gs);

    return 0;
}