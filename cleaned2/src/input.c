#include "input.h"
#include <SDL2/SDL.h>
#include "gamestate.h"
#include "menu.h"
#include "SDL2/SDL_rect.h"



void process_input(struct MainChar *mChar, struct 
CloseButton *cButton) {
    SDL_Event event;
    const uint8_t *keyState = SDL_GetKeyboardState(NULL);
     // Get delta_time factor converted to seconds to be used to update objects
    static Uint32 last_frame_time = 0;
    if (last_frame_time == 0) {
        last_frame_time = SDL_GetTicks();
    }
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    // Store the milliseconds of the current frame to be used in the next one
    last_frame_time = SDL_GetTicks();
    
    const float MOVEMENT_SPEED = 300.0f; // pixels per second

    if(keyState[SDL_SCANCODE_W]) mChar->y -= MOVEMENT_SPEED * delta_time;  // Was modifying rect.y
    if(keyState[SDL_SCANCODE_S]) mChar->y += MOVEMENT_SPEED * delta_time;  // Was modifying rect.y
    if(keyState[SDL_SCANCODE_A]) mChar->x -= MOVEMENT_SPEED * delta_time;  // Was modifying rect.x
    if(keyState[SDL_SCANCODE_D]) mChar->x += MOVEMENT_SPEED * delta_time;  // Was modifying rect.x

    // Update the rect with rounded integer positions
    mChar->rect.x = (int)mChar->x;
    mChar->rect.y = (int)mChar->y;

    
    
    // Handle one-time events
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                currentState = GAME_QUIT;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if(currentState == GAME_RUNNING)
                            currentState = GAME_PAUSED;
                        else if(currentState == GAME_PAUSED)
                            currentState = GAME_RUNNING;
                        break;
                    
                    // Add more single-press keys here
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    struct SDL_Point mousePoint = {
                        mousePoint.x = event.button.x,
                        mousePoint.y = event.button.y
                    };
                    // feed it the point and the rect
                    // the point in space is 2d so it 
                    // has both x and y
                    if (SDL_PointInRect(&mousePoint, &cButton->rect)) {
                        currentState = GAME_RUNNING;
                    }
                }
                break;
        }
    }
}