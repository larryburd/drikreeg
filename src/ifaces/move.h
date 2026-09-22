#ifndef MOVE_H
#define MOVE_H

struct GameState;
struct Piece;
enum ActionType;

enum ActionType {
    MOVE,
    ATTACK,
    HEAL
};

/*
 * Struct: Move
 * Represents a single action/move a piece wants to perform.
 * Used by AI to generate possible moves and by game logic to execute moves.
 * 
 * Fields:
 *   fromX, fromY: Starting position of the acting piece
 *   toX, toY: Target position (destination for MOVE, target for ATTACK/HEAL)
 *   action: Type of action being performed
 *   pieceIndex: Index into GameState.pieces array for quick piece lookup
 */
struct Move {
    int fromX, fromY;           // Source position (which piece is acting)
    int toX, toY;               // Target position
    enum ActionType action;     // What type of action
    int pieceIndex;             // Index into pieces array for quick lookup
};

struct Move* createMove(struct Piece* piece, int toX, int toY, enum ActionType action);
int isMoveLegal(struct GameState* gs, struct Move* move);
char* actionToString(enum ActionType type);
int movePiece(struct GameState* gs, struct Move* move);

#endif