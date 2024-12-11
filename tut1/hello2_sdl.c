#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

int main(void) {

    // init video and timer
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    // SDL window struct win
    SDL_Window *win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if (!win) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // add a delay
    SDL_Delay(10000);

    // clean up resources
    SDL_DestroyWindow(win);
    SDL_Quit();
}