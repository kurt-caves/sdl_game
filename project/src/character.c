#include "character.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

int Character_Init(struct Character *character, SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h ) {
    character->texture = IMG_LoadTexture(renderer, imagePath);
    if (!character->texture) {
        fprintf(stderr, "Failed to load character texture %s\n", SDL_GetError());
        return 1;
    }

    // set position and size of character
    character->rect = (SDL_Rect){x,y,w,h};
    return 1;
}

