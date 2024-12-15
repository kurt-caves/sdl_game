
#include "main_character.h"

void init_char(struct Mage *mage, int x, int y, int width, int height) {
    mage->rect = (SDL_Rect){x, y, width, height};
}