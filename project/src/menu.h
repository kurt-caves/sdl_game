#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <SDL2/SDL.h>

/*
SDL_Texture represents the graphical content of a button

SDL_Rect Defines the position and dimensions of a button the screen
*/

struct  {
    SDL_Texture *background;
    SDL_Texture *exitButton;
    SDL_Rect *exButton;

} PauseMenu;

int PauseMenu_Init(struct PauseMenu *pMenu, SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h);


#endif