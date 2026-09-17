#ifndef GAME_STATE
#define GAME_STATE

/* 
 * Data structures to hold the game's items (board, pieces, player state, etc).
 * Defines the core game model used throughout the application.
 */

enum Players {
    PLAYER_ONE,
    PLAYER_TWO
};

/* Game piece look ups */
extern const char pieceSymbols[];

/* 
 * Enum: RangeType
 * Determines how a piece's attack/heal range is calculated.
 * STRAIGHTLINE: Only affects targets along cardinal directions (up, down, left, right)
 * CIRCLE: Affects targets in all directions within range (including diagonals)
 */
enum RangeType {
    STRAIGHTLINE,
    CIRCLE
};

/*
 * Enum: PieceType
 * Identifies which of the three piece types a piece is.
 * MELEE: Attacks adjacent squares (1 square range)
 * RANGED: Attacks 2-3 squares away in straight lines
 * HEALER: Heals adjacent allied pieces (1 square range)
 */
enum PieceType {
    MELEE,
    RANGED,
    HEALER
};

/*
 * Struct: Piece
 * Represents a game piece (unit) on the board.
 * All three piece types use this unified structure.
 * 
 * Fields:
 *   y, x: Position on the 6x6 board (0-5)
 *   health: Current health points. Piece is dead when health <= 0
 *   range: Maximum range for attacks/heals
 *   minRange: Minimum range (only applicable for RANGED pieces)
 *   power: Attack damage (for MELEE/RANGED) or healing amount (for HEALER)
 *   mvLimit: Maximum squares this piece can move per turn
 *   rangeType: Whether this piece affects targets in straight lines or circles
 *   pieceType: Type of piece (MELEE, RANGED, or HEALER)
 *   player: Owner of the piece (1 or 2)
 */
struct Piece {
    int y, x;
    int health;
    int range;
    int minRange;
    int power;
    int mvLimit;
    char icon;
    enum RangeType rangeType;
    enum PieceType pieceType;
    int player;
};

/*
 * Enum: GamePhase
 * Represents the current state of the game.
 * PLAYING: Game is in progress
 * DRAW: Game ended in a draw
 * PLAYER_1_WINS: Player 1 has won
 * PLAYER_2_WINS: Player 2 has won
 */
enum GamePhase {
    PLAYING,
    DRAW,
    PLAYER_1_WINS,
    PLAYER_2_WINS
};

/*
 * Struct: GameState
 * Holds the entire game state (board and pieces).
 * This is the main data structure passed through game logic and rendering.
 * 
 * Fields:
 *   boardMax_X, boardMax_Y: Board dimensions (6x6 for this game)
 *   currPlayer: Which player's turn it is 
 *   pieces[6]: Array of pointers to the 6 pieces in play (3 per player)
 *   gamePhase: Current state of the game (playing, draw, or winner declared)
 *   actionHistroy[3][100]: A log of the last three actions to be taken
 *   actionCount: The number of moves taken throughout the whole game
 */
struct GameState {
    int boardMax_X;
    int boardMax_Y;
    enum Players currPlayer;
    struct Piece* pieces[6];
    enum GamePhase gamePhase;
    char actionHistory[3][100];
    int actionCount;

};

/*
 * Enum: ActionType
 * Specifies what type of action a piece is performing.
 * MOVE: Piece is moving to a new position
 * ATTACK: Piece is attacking a target
 * HEAL: Piece is healing an allied target
 */
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

struct GameState* game_init();

#endif
