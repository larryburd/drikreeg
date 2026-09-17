#include "../ifaces/game_state.h"
#include <stdlib.h>

const char pieceSymbols[] = {
    '%', // Melee
    '&', // Ranged
    '@', // Healer
    '.'  // Empty square
};

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
