// https://www.youtube.com/watch?v=XfZ6WrV5Z7Y

#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error init SDL\n");
        return FALSE;
    }

    // make a window
    // null for title
    // x and y position centered
    // width and height
    // flags
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
        );
    if(!window) {
        fprintf(stderr, "Error init SDL window\n");
        return FALSE;
    }

    // what do we want to render to screen
    // first is the window
    // -1 gets the default driver
    //  no flags so 0
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error init SDL renderer\n");
        return FALSE;
    }

    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        // clicking the x button on the window to quit
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
        
    }
}

void setup() {
    
}

void update() {
    //update
}

void render() {

}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {

    // init SDL window
    game_is_running = init_window();

    setup();

    // only run if we can init the window
    // something inside process_input() will set game is running
    // to false
    while(game_is_running) {

        // the holy trinity the game loop
        process_input();
        update();
        render();
        // the holy trinity the game loop
    }

    // when the game process ends
    destroy_window();
    return 0;
}