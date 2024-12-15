#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

extern bool game_is_running;
extern bool game_is_paused;

void init_game_state(void);

#endif