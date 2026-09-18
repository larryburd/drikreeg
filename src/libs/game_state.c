/**
 * game_state.c
 *
 * Game state management and initialization for Tri Krieg.
 * Handles piece creation and game state setup.
 */

#include "../ifaces/game_state.h"
#include <stdlib.h>
#include <stdio.h>

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
struct Piece* create_piece(int y, int x, int player, int type) {
    struct Piece* piece = malloc(sizeof(struct Piece));

    int health, range, minRange, power, mvLimit, rangeType;
    char icon;

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
            mvLimit = 3;
            break;
        case RANGED:
            /* Ranged attacker - medium health, distant range, high movement */
            icon = pieceSymbols[1];
            health = 30;
            range = 3;
            rangeType = STRAIGHTLINE;
            minRange = 2;
            power = 15;
            mvLimit = 4;
            break;
        case HEALER:
            /* Support unit - low health, medium range heal, moderate movement */
            icon = pieceSymbols[2];
            health = 20;
            range = 2;
            minRange = 1;
            rangeType = CIRCLE;
            power = 8;
            mvLimit = 3;
            break;
        default:
            /* Invalid piece type */
            printf("Unknown piece type\n");
            break;
    }

    /* Initialize piece with calculated attributes and provided location/owner */
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
 * TODO: Allocate and initialize the 6 pieces (3 per player)
 */
struct GameState* game_init() {
    /* Allocate memory for game state */
    struct GameState* gs = malloc(sizeof(struct GameState));

    /* Set board dimensions */
    gs->boardMax_X = 6;
    gs->boardMax_Y = 6;

    /* TODO: Create 6 pieces total (3 for each player) with starting positions */
    /* Example: gs->pieces[0] = create_piece(0, 0, PLAYER_ONE, MELEE); */
    gs->pieces[0] = create_piece(0, 1, PLAYER_ONE, MELEE);
    gs->pieces[1] = create_piece(0, 2, PLAYER_ONE, HEALER);
    gs->pieces[2] = create_piece(0, 3, PLAYER_ONE, RANGED);

    gs->pieces[3] = create_piece(5, 1, PLAYER_TWO, MELEE);
    gs->pieces[4] = create_piece(5, 2, PLAYER_TWO, HEALER);
    gs->pieces[5] = create_piece(5, 3, PLAYER_TWO, RANGED);

    /* Initialize game state */
    gs->currPlayer = PLAYER_ONE;
    gs->gamePhase = PLAYING;
    gs->actionCount = 0;

    return gs;
}
