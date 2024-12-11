#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL2/SDL.h>

struct Character {
    SDL_Texture *texture;
    SDL_Rect rect;
};

int Character_Init(struct Character *character, SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h );

#endif