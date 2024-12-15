#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_QUIT
} GameState;

GameState currentState;

#endif