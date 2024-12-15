#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include <SDL2/SDL.h>

struct Mage {
    SDL_Rect rect;
};

// used to set rect of character
void init_char(struct Mage *mage, int x, int y, int width, int height);

#endif