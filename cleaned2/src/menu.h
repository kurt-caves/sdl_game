#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <stdbool.h>

struct CloseButton {
    SDL_Rect rect;
    bool pressed;
};

// struct QuitButton {
//     SDL_Rect rect;
//     bool pressed;
// };

void init_close_button(struct CloseButton *cButton, int x, int y, int width, int height);
// void init_quit_button(struct QuitButton *qButton, int x, int y, int width, int height);



#endif