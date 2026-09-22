#ifndef MESSAGES_H
#define MESSAGES_H

struct GameState;
struct Move;

void moveMsg(char* msg, int msgSize, int currPlayer, struct Move* move, struct GameState* gs);

#endif