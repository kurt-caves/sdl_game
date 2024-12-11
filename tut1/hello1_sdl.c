#include <stdio.h>
#include <SDL2/SDL.h>
// #include <SDL/SDL_error.h>

int main(void) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    printf("Initialization succesful\n");

    // clean up resources
    SDL_Quit();
}