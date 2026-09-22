/**
 * game_state.c
 *
 * Game state management and initialization for Tri Krieg.
 * Handles piece creation and game state setup.
 */

#include "../ifaces/game_state.h"
#include "../ifaces/move.h"
#include "../ifaces/messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Array of symbols used to represent different piece types on the board.
 * Index corresponds to PieceType enum values.
 */
const char pieceSymbols[] = {
    '%', // Melee
    '&', // Ranged
    '@', // Healer
    '.'  // Empty square
};

/**
 * create_piece - Initializes a new game piece with type-specific attributes.
 *
 * @param y: Y coordinate on the game board
 * @param x: X coordinate on the game board
 * @param player: Owner of the piece (PLAYER_ONE or PLAYER_TWO)
 * @param type: Type of piece to create (MELEE, RANGED, or HEALER)
 *
 * @return: Pointer to newly created Piece struct with initialized attributes
 *
 * Sets piece-specific stats based on type:
 *   - MELEE: High health, 1 range attack, 3 movement
 *   - RANGED: Medium health, 2-3 range attack, 4 movement
 *   - HEALER: Low health, 2 range heal, 3 movement
 */
struct Piece* create_piece(int index, int y, int x, int player, int type) {
    struct Piece* piece = malloc(sizeof(struct Piece));

    int health, range, minRange, power, mvLimit, rangeType;
    char icon = '\0';

    /* Determine piece attributes based on type */
    switch (type) {
        case MELEE:
            /* Melee attacker - high health, close range, moderate movement */
            icon = pieceSymbols[0];
            health = 40;
            range = 1;
            minRange = 1;
            rangeType = CIRCLE;
            power = 10;
            mvLimit = 7;
            break;
        case RANGED:
            /* Ranged attacker - medium health, distant range, high movement */
            icon = pieceSymbols[1];
            health = 30;
            range = 3;
            rangeType = STRAIGHTLINE;
            minRange = 2;
            power = 15;
            mvLimit = 10;
            break;
        case HEALER:
            /* Support unit - low health, medium range heal, moderate movement */
            icon = pieceSymbols[2];
            health = 20;
            range = 2;
            minRange = 1;
            rangeType = CIRCLE;
            power = 8;
            mvLimit = 7;
            break;
        default:
            /* Invalid piece type */
            printf("Unknown piece type\n");
            return piece;
            break;
    }

    /* Initialize piece with calculated attributes and provided location/owner */
    piece->index = index;
    piece->y = y;
    piece->x = x;
    piece->health = health;
    piece->range = range;
    piece->minRange = minRange;
    piece->power = power;              /* Damage dealt or healing amount */
    piece->mvLimit = mvLimit;          /* Squares this piece can move per turn */
    piece->player = player;
    piece->icon = icon;
    piece->rangeType = rangeType;
    piece->pieceType = type;

    return piece;
    
}

/**
 * game_init - Initializes the game state with default values.
 *
 * @return: Pointer to newly allocated GameState struct
 *
 * Sets up:
 *   - 6x6 game board dimensions
 *   - Starting player (PLAYER_ONE)
 *   - Game phase (PLAYING)
 *   - Action history counter
 *
 */
struct GameState* game_init() {
    /* Allocate memory for game state */
    struct GameState* gs = malloc(sizeof(struct GameState));

    /* Set board dimensions */
    gs->boardMax_X = 15;
    gs->boardMax_Y = 13;

    /* Find center of the row to place pieces */
    int start_x = gs->boardMax_X / 2;

    /* TODO: Create 6 pieces total (3 for each player) with starting positions */
    /* Example: gs->pieces[0] = create_piece(0, 0, PLAYER_ONE, MELEE); */
    gs->pieces[0] = create_piece(0, 0, start_x, PLAYER_ONE, MELEE);
    gs->pieces[1] = create_piece(1, 0, start_x + 1, PLAYER_ONE, HEALER);
    gs->pieces[2] = create_piece(2, 0, start_x - 1, PLAYER_ONE, RANGED);

    gs->pieces[3] = create_piece(3, gs->boardMax_Y - 1, start_x, PLAYER_TWO, MELEE);
    gs->pieces[4] = create_piece(4, gs->boardMax_Y - 1, start_x + 1, PLAYER_TWO, HEALER);
    gs->pieces[5] = create_piece(5, gs->boardMax_Y - 1, start_x - 1, PLAYER_TWO, RANGED);

    /* Initialize game state */
    gs->currPlayer = PLAYER_ONE;
    gs->gamePhase = PLAYING;
    gs->actionCount = 0;

    return gs;
}

/* Change the current player and increment actions taken */
void changeTurns(struct GameState* gs) {
    if (gs->currPlayer == PLAYER_ONE) {
        gs->currPlayer = PLAYER_TWO;
    } else {
        gs->currPlayer = PLAYER_ONE;
    }

    gs->actionCount++;

    return;
}

void addActionHist(struct GameState* gs, char* msg){
    /* find the first empty message array */
    for (int i = 0; i < MESSAGELOGLEN; i++) {
        if (gs->actionHistory[i][0] == '\0') {
            strncpy(gs->actionHistory[i], msg, MAXMSGSIZE);
            return;
        }
    }

    /*  Msg queue is full.
        Remove the first message, move the other two up one,
        and add the new one to the last index */
    for (int i = 0; i < MESSAGELOGLEN; i++) {
        strncpy(gs->actionHistory[i], gs->actionHistory[i + 1], MAXMSGSIZE);
    }
    
    strncpy(gs->actionHistory[MESSAGELOGLEN - 1], msg, MAXMSGSIZE);
    return;
}

