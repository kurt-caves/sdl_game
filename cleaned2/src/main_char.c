#include "main_char.h"
#include <SDL2/SDL_image.h>

void init_char(struct MainChar *mChar, float x, float y, int width, int height) {
    mChar->x = x;
    mChar->y = y;
    mChar->rect = (SDL_Rect){(int)x, (int)y, width, height};
}