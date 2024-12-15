#ifndef INIT_H
#define INIT_H


#include "main_char.h"
#include "menu.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *bgTexture;
SDL_Texture *mainChar;
SDL_Texture *menuTexture;
SDL_Texture *buttonTexture;

int init_window(void);
void render(
    struct MainChar *mChar, 
    struct CloseButton *cButton
    );
void destroy_window(void);

#endif