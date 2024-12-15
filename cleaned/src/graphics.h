#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "main_character.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *bgTexture;
SDL_Texture *mainChar;

int init_window(void);
void render(struct Mage *mage);
void destroy_window(void);

#endif