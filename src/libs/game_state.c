#include "../ifaces/game_state.h"
#include <stdlib.h>
#include <stdio.h>

const char pieceSymbols[] = {
    '%', // Melee
    '&', // Ranged
    '@', // Healer
    '.'  // Empty square
};

struct Piece* create_piece(int y, int x, int player, int type) {
    struct Piece* piece;
    int health, range, minRange, power, mvLimit, rangeType;
    char icon;
    
    piece->y = y;
    piece->x = x;

    switch (type) {
        case MELEE:
            icon = pieceSymbols[0];
            health = 40;
            range = 1;
            minRange = 1;
            rangeType = CIRCLE;
            power = 10;
            mvLimit = 3;
            break;
        case RANGED:
            icon = pieceSymbols[1];
            health = 30;
            range = 3;
            rangeType = STRAIGHTLINE;
            minRange = 2;
            power = 15;
            mvLimit = 4;
            break;
        case HEALER:
            icon = pieceSymbols[2];
            health = 20;
            range = 2;
            minRange = 1;
            rangeType = CIRCLE;
            power = 8;
            mvLimit = 3;
            break;
        default:
            printf("Unknown piece type\n");
            break;
    }
    piece->health = health;
    piece->range = range;
    piece->minRange = minRange;
    piece->power = power;
    piece->mvLimit = mvLimit;
    piece->player = player;
    piece->icon = icon;
    piece->rangeType = rangeType;
    piece->pieceType = type;

    return piece;
    
}

struct GameState* game_init() {
    struct GameState* gs = malloc(sizeof(struct GameState));

    // Board Setup
    gs->boardMax_X = 6;
    gs->boardMax_Y = 6;

    // Crete 6 pieces
    //gs->pieces[0] = create_piece(MELEE, PLAYER_ONE
    
    gs->currPlayer = PLAYER_ONE;
    gs->gamePhase = PLAYING;
    gs->actionCount = 0;

    return gs;
}
