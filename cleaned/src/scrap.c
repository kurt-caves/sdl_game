#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"

int game_is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *bgTexture = NULL;
SDL_Texture *mainChar = NULL;

struct Mage {
    SDL_Rect rect;
};

void init_char(struct Mage *mage, int x, int y, int width, int height) {
    mage->rect = (SDL_Rect){x, y, width, height};
}

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

void process_input(struct Mage *mage) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game_is_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game_is_running = false;
                }
                break;
        }
        
    }
    
    
    
}

void setup(void) {

}

void update(void) {

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

int main(void) {

    game_is_running = init_window();

    setup();
    struct Mage *mage = malloc(sizeof(struct Mage));
    init_char(mage, 0, 0, 32, 32);
    const uint8_t *keyState = SDL_GetKeyboardState(NULL);
    while(game_is_running) {
        SDL_PumpEvents();
        if(keyState[SDL_SCANCODE_W]) mage->rect.y -= 1;
        if(keyState[SDL_SCANCODE_S]) mage->rect.y += 1;
        if(keyState[SDL_SCANCODE_A]) mage->rect.x -= 1;
        if(keyState[SDL_SCANCODE_D]) mage->rect.x += 1;
        process_input(mage);
        update();
        render(mage);
    }

    destroy_window();

    return 0;
}



build:
	gcc -Wall -std=c99 ./src/*.c `sdl2-config --cflags --libs` -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2_image -lm -o game

run:
	./game

clean:
	rm -f game