#include <stdlib.h>
#include "game.h"
#include "game_state.h"
#include "graphics.h"
#include "input.h"
#include "main_character.h"


int main(void) {
    init_game_state();
    game_is_running = init_window();

    setup();
    struct Mage *mage = malloc(sizeof(struct Mage));
    init_char(mage, 0, 0, 32, 32);
    
    while(game_is_running) {
        SDL_PumpEvents();
        handle_keyboard_input(mage);
        process_input(mage);
        update();
        render(mage);
    }

    destroy_window();
    free(mage);
    return 0;
}