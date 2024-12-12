#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "character.h"

int main(void) {
    // initialize SDL and check for errors
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // initialize SDL_image to load jpg and png images
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // create the window, name, x pos, y pos, width, heigh, shown
    // 800 is the width, 600 is the height
    // SDL_Window holds all information about the game window
    SDL_Window *window = SDL_CreateWindow("Game Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // SDL_Renderer handles all rendering and is tied to SDL_Window so that you only render inside the game window
    // takes a point to the window being rendered, -1: get the first driver renderer of parameter 3
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load background image
    SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "assets/map.png");
    if (bgTexture == NULL) {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *pauseMenu = IMG_LoadTexture(renderer, "assets/background.png");
    if (bgTexture == NULL) {
        fprintf(stderr, "IMG_LoadTexture Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // load in the main character
    struct Character character;
    if(!Character_Init(&character, renderer, "assets/mage.png", 100, 100, 32, 32)) {
        fprintf(stderr, "Failed to initialize main character: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    bool running = true;
    bool isPaused = false;
    const uint8_t *keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (running) {
        // Handle events
        SDL_PumpEvents();
        // -----------------------------------
        // for wasd
        if(keyState[SDL_SCANCODE_W]) character.rect.y -= 3;
        if(keyState[SDL_SCANCODE_S]) character.rect.y += 3;
        if(keyState[SDL_SCANCODE_A]) character.rect.x -= 3;
        if(keyState[SDL_SCANCODE_D]) character.rect.x += 3;
        
        // -----------------------------------

        

        while (SDL_PollEvent(&event)) {
           

            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isPaused = !isPaused;
            }

            }

            // Clear screen
            SDL_RenderClear(renderer);

            // Render background
            SDL_RenderCopy(renderer, bgTexture, NULL, NULL);


            // render main character
            SDL_RenderCopy(renderer, character.texture, NULL, &character.rect);

            if(isPaused) {
                SDL_RenderCopy(renderer, pauseMenu, NULL, NULL);
            }

            // render pause menu
            // if(keyState[SDL_SCANCODE_ESCAPE]) {
            //     SDL_RenderCopy(renderer, pauseMenu, NULL, NULL);
            //     printf("escape\n");
            // }

            // Present renderer
            SDL_RenderPresent(renderer);
    }

    // Cleanup
    // SDL_DestroyTexture(menuTexture);
    // SDL_DestroyTexture(main_character.texture);
    SDL_DestroyTexture(pauseMenu);
    SDL_DestroyTexture(character.texture);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;

}