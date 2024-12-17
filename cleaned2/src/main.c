#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "main_char.h"
#include "gamestate.h"
#include "init_render_clean.h"
#include "input.h"
#include "menu.h"

int last_frame_time;

void setup(void) {

}

// logic to keep a fixed time step
void update(void) {
   
}



int main(void) {


    currentState = init_window();

    setup();
    struct MainChar *mChar = malloc(sizeof(struct MainChar ));
    init_char(mChar, 0.0, 0.0, 48, 48);

    struct CloseButton *cButton = malloc(sizeof(struct CloseButton));
    init_close_button(cButton, 768, 0, 32, 32);

    // struct QuitButton *qButton = malloc(sizeof(struct QuitButton));
    // init_close_button(qButton, 400, 300, 96, 25);
    
    while(currentState != GAME_QUIT) {

        

        SDL_PumpEvents();
        process_input(mChar, cButton);
        update();
        render(mChar, cButton);
    }

    destroy_window();
    free(mChar);
    free(cButton);

    return 0;
}
