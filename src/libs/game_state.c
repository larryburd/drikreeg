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
    gs->boardMax_X = 15;
    gs->boardMax_Y = 13;

    /* Find center of the row to place pieces */
    int start_x = gs->boardMax_X / 2;

    /* TODO: Create 6 pieces total (3 for each player) with starting positions */
    /* Example: gs->pieces[0] = create_piece(0, 0, PLAYER_ONE, MELEE); */
    gs->pieces[0] = create_piece(0, start_x, PLAYER_ONE, MELEE);
    gs->pieces[1] = create_piece(0, start_x + 1, PLAYER_ONE, HEALER);
    gs->pieces[2] = create_piece(0, start_x - 1, PLAYER_ONE, RANGED);

    gs->pieces[3] = create_piece(gs->boardMax_Y - 1, start_x, PLAYER_TWO, MELEE);
    gs->pieces[4] = create_piece(gs->boardMax_Y - 1, start_x + 1, PLAYER_TWO, HEALER);
    gs->pieces[5] = create_piece(gs->boardMax_Y - 1, start_x - 1, PLAYER_TWO, RANGED);

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
int is_move_legal(struct GameState* gs, struct Piece* piece, int target_x, int target_y) {
    /* Check if target is within board bounds */
    if (target_x < 0 || target_x >= gs->boardMax_X || 
        target_y < 0 || target_y >= gs->boardMax_Y) {
        return -1;  /* Out of bounds */
    }
    
    /* Calculate Manhattan distance (total squares to travel) */
    int distance = abs(piece->x - target_x) + abs(piece->y - target_y);
    
    /* Check if distance exceeds movement limit */
    if (distance > piece->mvLimit) {
        return -1;  /* Too far to move */
    }
    
    /* Check if another piece occupies the destination */
    for (int i = 0; i < 6; i++) {
        if (gs->pieces[i] != NULL && 
            gs->pieces[i] != piece &&  /* Don't check the piece against itself */
            gs->pieces[i]->x == target_x && 
            gs->pieces[i]->y == target_y) {
            return -1;  /* Space occupied */
        }
    }
    
    return 0;  /* Move is legal */
}
