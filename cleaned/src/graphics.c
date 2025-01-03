#include "graphics.h"
#include "constants.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int init_window(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if (!window) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        return false;
    }

    // load image into memory
    bgTexture = IMG_LoadTexture(renderer, "map.png");
    if (!bgTexture) {
        fprintf(stderr, "IMG_LoadTexture Error map.png: %s\n", IMG_GetError());
        return false;
    }
    // load image into memory
    mainChar = IMG_LoadTexture(renderer, "mage.png");
    if (!bgTexture) {
        fprintf(stderr, "IMG_LoadTexture Error mage.png: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void render(struct Mage *mage) {
    
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    SDL_RenderCopy(renderer, mainChar, NULL, &mage->rect);
    SDL_RenderPresent(renderer);

}

void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(bgTexture);
    SDL_Quit();
}
