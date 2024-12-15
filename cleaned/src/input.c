#include "input.h"
#include "game_state.h"
#include "SDL2/SDL.h"

void handle_keyboard_input(struct Mage *mage) {
    const uint8_t *keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_W]) mage->rect.y -= 1;
    if(keyState[SDL_SCANCODE_S]) mage->rect.y += 1;
    if(keyState[SDL_SCANCODE_A]) mage->rect.x -= 1;
    if(keyState[SDL_SCANCODE_D]) mage->rect.x += 1;
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