#include "menu.h"


void init_close_button(struct CloseButton *cButton, int x, int y, int width, int height) {
    cButton->rect = (SDL_Rect){x,y,width,height};
    cButton->pressed = false;
}

// void init_quit_button(struct QuitButton *qButton, int x, int y, int width, int height) {
//     qButton->rect = (SDL_Rect){x,y,width,height};
//     qButton->pressed = false;
// }