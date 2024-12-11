#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL2/SDL.h>

struct Character {
    SDL_Texture *texture;
    SDL_Rect rect;
};

// takes:
// character struct
// the renderer struct
// the path to the image
// x,y coords where the image will be loaded on the screen
// the width and height of the image
int Character_Init(struct Character *character, SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h );



#endif