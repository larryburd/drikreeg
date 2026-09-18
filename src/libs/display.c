#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include "../ifaces/display.h"
#include "../ifaces/game_state.h"

/* Initialize the ncurses display library */
int display_init() {
    /* Minimum screen size needed */
    const int X_MIN = 80;
    const int Y_MIN = 24;

    int max_x, max_y;

    initscr();

    /* Check that we have enough screen realestate */
    getmaxyx(stdscr, max_y, max_x);
    if (max_x < X_MIN || max_y < Y_MIN) {
        printf("Screen area is too small.  Ensure there is %d x %d columns and rows, then try again", X_MIN, Y_MIN);

        return -1;
    }

    noecho();
    cbreak();
    start_color();
    curs_set(0);
    init_pair(PLAYER_ONE, COLOR_RED, COLOR_BLACK);  // Player one colors
    init_pair(PLAYER_TWO, COLOR_BLUE, COLOR_BLACK); // Player two colors
    return 0;
}

int display_cleanup() {
    endwin();
    return 0;
}

int display_render_board(struct GameState* gs) {
    const int SCREENBUFFER_X = 2;
    const int SCREENBUFFER_Y = 2;
    const int boardWidth = gs->boardMax_X * 2;
    bool isPiece;

    for (int y = SCREENBUFFER_Y; y < SCREENBUFFER_Y + gs->boardMax_Y; ++y) {
        for (int x = SCREENBUFFER_X; x < SCREENBUFFER_X + boardWidth; x+=2) {
            isPiece = false;
            char symbol = pieceSymbols[3]; // Default to empty square
            
            // Check if any piece is at this board position
            for (int i = 0; i < 6; ++i) {
                if (gs->pieces[i] != NULL && 
                    gs->pieces[i]->x * 2 + SCREENBUFFER_X == x && 
                    gs->pieces[i]->y + SCREENBUFFER_Y == y) {
                    symbol = gs->pieces[i]->icon;
                    attron(A_BOLD | COLOR_PAIR(gs->pieces[i]->player));
                    isPiece = true;
                    break; // Found piece, stop checking
                }
            }
            
            mvaddch(y, x, symbol); // Draw either piece or empty square
            if (isPiece)
                standend();
        }
    }
    return 0;
}
/**
 * display_render_status - Renders the game status on the right side of the screen.
 * 
 * @param gs: Pointer to the GameState
 * 
 * Displays:
 *   - Current player's turn
 *   - All pieces for each player (type, health, position)
 *   - Total actions taken
 */
int display_render_status(struct GameState* gs) {
    const int STATUS_X = 50;  /* Start status display at column 50 */
    const int STATUS_Y = 2;   /* Start at row 2 (matching board) */
    
    int row = STATUS_Y;
    const char* piece_types[] = {"MELEE", "RANGED", "HEALER"};
    const char* player_names[] = {"PLAYER 1", "PLAYER 2"};
    
    /* Display current player */
    attron(A_BOLD);
    mvprintw(row, STATUS_X, "Turn: %s", player_names[gs->currPlayer]);
    attroff(A_BOLD);
    row += 2;
    
    /* Display Player 1 pieces */
    attron(A_BOLD | COLOR_PAIR(PLAYER_ONE));
    mvprintw(row, STATUS_X, "=== PLAYER 1 ===");
    attroff(A_BOLD | COLOR_PAIR(PLAYER_ONE));
    row++;
    
    for (int i = 0; i < 3; i++) {
        struct Piece* piece = gs->pieces[i];
        if (piece != NULL) {
            mvprintw(row, STATUS_X, "[%c] %s:\t HP:%d (%d,%d)", 
                     piece->icon,
                     piece_types[piece->pieceType],
                     piece->health,
                     piece->x,
                     piece->y);
        }
        row++;
    }
    row++;
    
    /* Display Player 2 pieces */
    attron(A_BOLD | COLOR_PAIR(PLAYER_TWO));
    mvprintw(row, STATUS_X, "=== PLAYER 2 ===");
    attroff(A_BOLD | COLOR_PAIR(PLAYER_TWO));
    row++;
    
    for (int i = 3; i < 6; i++) {
        struct Piece* piece = gs->pieces[i];
        if (piece != NULL) {
            mvprintw(row, STATUS_X, "[%c] %s:\t HP:%d (%d,%d)", 
                     piece->icon,
                     piece_types[piece->pieceType],
                     piece->health,
                     piece->x,
                     piece->y);
        }
        row++;
    }
    row++;
    
    /* Display action count */
    attron(A_BOLD);
    mvprintw(row, STATUS_X, "Actions: %d", gs->actionCount);
    attroff(A_BOLD);
    
    return 0;
}

/**
 * display_render_message - Displays a message to the player.
 * 
 * @param message: The message string to display
 * 
 * Renders the message at the bottom of the screen in the message log area.
 */
int display_render_message(const char* message) {
    const int MESSAGE_X = 2;
    const int MESSAGE_Y = 20;  /* Bottom of screen */
    
    if (message == NULL) {
        return -1;
    }
    
    /* Clear the message area first (2 rows for message display) */
    for (int i = 0; i < 2; i++) {
        mvprintw(MESSAGE_Y + i, MESSAGE_X, "                                                                            ");
    }
    
    /* Display the message */
    attron(A_BOLD);
    mvprintw(MESSAGE_Y, MESSAGE_X, ">> %s", message);
    standend();
    
    return 0;
}

int display_refresh(struct GameState* gs) {
    if (display_render_status(gs) != 0) {
        return -1;
    } else if (display_render_board(gs) != 0) {
        return -1;
    }
    refresh();
    return 0;
}

int display_animate_piece_move(struct GameState* gs, struct Piece* piece, int target_x, int target_y) {
    const int FRAME_DELAY_MS = 500; 
    const int FRAME_DELAY_US = FRAME_DELAY_MS * 1000; // conver to microseconds

    /* Move one square at a time toward the target */
    while (piece->x != target_x || piece->y != target_y) {
        /* Move closer to target x */
        if (piece->x < target_x) {
            piece->x++;
        } else if (piece->x > target_x) {
            piece->x--;
        }

        /* move closer to target y */
        if (piece->y < target_y) {
            piece->y++;
        } else if (piece->y > target_y) {
            piece->y--;
        }

        /* Redraw board */
        clear();
        //display_render_board(gs);
        display_refresh(gs);

        /* Sleep between frames */
        usleep(FRAME_DELAY_US);
    }

    return 0;
}
