#ifndef MAIN_CHAR_H
#define MAIN_CHAR_H

#include <SDL2/SDL.h>

struct MainChar {
    SDL_Rect rect;
    float x;
    float y;
};

void init_char(struct MainChar *mChar, float x, float y, int width, int height);

#endif