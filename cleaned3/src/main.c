#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

#define MAX_TEXTURES 50
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// for main menu
#define MENU_BACKGROUND_TEXTURE 2
#define MENU_CLOSE_BUTTON_TEXTURE 3
#define MENU_POINTER_TEXTURE 4
#define MENU_CONTINUE_BUTTON_TEXTURE 5
#define MENU_OPTIONS_BUTTON_TEXTURE 6
#define MENU_QUIT_BUTTON_TEXTURE 7


typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
    bool visible;
} Entity;

// main player
struct MainChar {
    float x;
    float y;
    SDL_Rect rect;
};

// main menu

struct MenuItem {
    SDL_Rect rect;
    char *text;
    bool isSelected;
};

struct MainMenu {
    SDL_Rect backgroundRect;
    SDL_Rect closeButtonRect;
    SDL_Rect pointerRect;
    struct MenuItem *menuItems;
    int itemCount;
    int selectedIndex;
    bool isVisible;
};

typedef struct {
   
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* textures[MAX_TEXTURES];
    int texture_count;

    struct MainChar *player;

    struct MainMenu mainMenu;

    TTF_Font *font;

    enum {
        GAME_RUNNING,
        GAME_PAUSED,
        GAME_QUIT
    } currentState;

} GameState;

int init_window(GameState *state) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        return 1;
    }

    // init font
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        return 1;
    }


    state->window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    
    if (!state->window) {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        return false;
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, 0);
    if (!state->renderer) {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        return false;
    }
    state->textures[0] = IMG_LoadTexture(state->renderer, "map.png");
    state->texture_count++;
    if (!state->textures[0]) {
        fprintf(stderr, "IMG_LoadTexture Error map.png: %s\n", IMG_GetError());
        return false;
    }
    state->textures[1] = IMG_LoadTexture(state->renderer, "mage.png");
    state->texture_count++;
    if (!state->textures[1]) {
        fprintf(stderr, "IMG_LoadTexture Error mage.png: %s\n", IMG_GetError());
        return false;
    }

    ////----------------------------------------------------------------------------------------
    /// main pause menu and it's items
    state->textures[MENU_BACKGROUND_TEXTURE] = IMG_LoadTexture(state->renderer, "main-menu.png");
    state->texture_count++;
    if (!state->textures[MENU_BACKGROUND_TEXTURE]) {
        fprintf(stderr, "IMG_LoadTexture Error main-menu.png: %s\n", IMG_GetError());
        return false;
    }

    state->textures[MENU_CLOSE_BUTTON_TEXTURE] = IMG_LoadTexture(state->renderer, "x_button.png");
    state->texture_count++;
    if (!state->textures[MENU_CLOSE_BUTTON_TEXTURE]) {
        fprintf(stderr, "IMG_LoadTexture Error x_button.png: %s\n", IMG_GetError());
        return false;
    }

    state->textures[MENU_POINTER_TEXTURE] = IMG_LoadTexture(state->renderer, "glove_pointer.png");
    state->texture_count++;
    if (!state->textures[MENU_POINTER_TEXTURE]) {
        fprintf(stderr, "IMG_LoadTexture Error glove_pointer.png: %s\n", IMG_GetError());
        return false;
    }

    ////----------------------------------------------------------------------------------------


    // Load your font
    state->font = TTF_OpenFont("Tiny RPG - Fine Fantasy Strategies.ttf", 64);
    if (!state->font) {
        fprintf(stderr, "Font loading error: %s\n", TTF_GetError());
        return 1;
    }



    state->currentState = GAME_RUNNING;
    return GAME_RUNNING;
}

void init_player(struct MainChar *player, float x, float y, int width, int height) {
    player->x = x;
    player->y = y;
    player->rect = (SDL_Rect){(int)x, (int)y, width, height};
}

void init_main_menu(struct MainMenu *menu) {
    // setup items in space
    menu->backgroundRect = (SDL_Rect){0,0, WINDOW_WIDTH, WINDOW_HEIGHT};
    menu->closeButtonRect = (SDL_Rect){768, 0, 32, 32};
    menu->pointerRect = (SDL_Rect){0, 0, 64, 64};
    menu->isVisible = false;

    // allocate memory for menu items
    menu->itemCount = 3;
    menu->menuItems = malloc(sizeof(struct MenuItem) * menu->itemCount);

    // center menu text buttons vertically
    int itemHeight = 50;
    int startY = (WINDOW_HEIGHT / 2) - (menu->itemCount * itemHeight);
    
    // continue button
    menu->menuItems[0] = (struct MenuItem){
        // x position from left
        // y position from top
        // width
        // height
        .rect = {WINDOW_WIDTH/2 - 100, startY, 200, itemHeight},
        .text = "Continue",
        .isSelected = true
    };

     // Options button
    menu->menuItems[1] = (struct MenuItem){
        .rect = {WINDOW_WIDTH/2 - 100, startY + itemHeight + 20, 200, itemHeight},
        .text = "Options",
        .isSelected = false
    };
    
    // Quit button
    menu->menuItems[2] = (struct MenuItem){
        .rect = {WINDOW_WIDTH/2 - 100, startY + (itemHeight + 20) * 2, 200, itemHeight},
        .text = "Quit",
        .isSelected = false
    };

}

void render_main_menu(GameState *state) {
    // render the background
    SDL_RenderCopy(state->renderer, state->textures[MENU_BACKGROUND_TEXTURE], NULL, &state->mainMenu.backgroundRect);

    // close button
    SDL_RenderCopy(state->renderer, state->textures[MENU_CLOSE_BUTTON_TEXTURE], NULL, &state->mainMenu.closeButtonRect);

    // render menu items
    // gold for selected item
    SDL_Color selectedColor = {255, 215, 0, 255};
    SDL_Color textColor = {255, 255, 255, 255};

    // loop through and render menu items
    for (int i = 0; i < state->mainMenu.itemCount; i++) {
        // make a pointer to the thing we need to render
        struct MenuItem *item = &state->mainMenu.menuItems[i];

        // render the text, if its selected make it gold
        SDL_Color currentColor = item->isSelected ? selectedColor : textColor;
        SDL_Surface *surface = TTF_RenderText_Blended(state->font, item->text, currentColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(state->renderer, surface);

        // Center text in button
        SDL_Rect textRect = item->rect;
        textRect.w = surface->w;
        textRect.h = surface->h;
        textRect.x = item->rect.x + (item->rect.w - surface->w) / 2;
        textRect.y = item->rect.y + (item->rect.h - surface->h) / 2;

        SDL_RenderCopy(state->renderer, texture, NULL, &textRect);
        
        // Render pointer next to selected item
        if (item->isSelected) {
            state->mainMenu.pointerRect.x = item->rect.x - state->mainMenu.pointerRect.w - 10;
            state->mainMenu.pointerRect.y = item->rect.y + (item->rect.h - state->mainMenu.pointerRect.h) / 2;
            SDL_RenderCopy(state->renderer, state->textures[MENU_POINTER_TEXTURE], NULL, &state->mainMenu.pointerRect);
        }
        
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

    }

}

void render(GameState *state) {
    SDL_RenderClear(state->renderer);
    // render main map
    SDL_RenderCopy(state->renderer,state->textures[0], NULL, NULL);
    // here we are rendering the main character and it's rect
    SDL_RenderCopy(state->renderer,state->textures[1], NULL, &state->player->rect);

    // render the main pause menu
    if (state->currentState == GAME_PAUSED) {
        render_main_menu(state);
    }

    SDL_RenderPresent(state->renderer);
}

void destroy_window(GameState *state) {
    if(state->player) {
        free(state->player);
    }
    if(state->renderer) {
        SDL_DestroyRenderer(state->renderer);
    }
    if(state->window) {
        SDL_DestroyWindow(state->window);
    }
    for(int i = 0; i < state->texture_count; i++) {
        SDL_DestroyTexture(state->textures[i]);
    }
    if(state->font) {
        TTF_CloseFont(state->font);
    }
    free(state);
    SDL_Quit();
}

void process_main_menu_input(GameState *state, SDL_Event *event) {
    struct MainMenu *menu = &state->mainMenu;
    switch(event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_DOWN:
                    // set selected to false
                    menu->menuItems[menu->selectedIndex].isSelected = false;
                    // update the selected index, modulo lets us start at 0 again
                    menu->selectedIndex = (menu->selectedIndex + 1) % menu->itemCount;
                    // set selected to true
                    menu->menuItems[menu->selectedIndex].isSelected = true;
                    break;
                case SDLK_UP:
                    // set selected to false
                    menu->menuItems[menu->selectedIndex].isSelected = false;
                    // update the selected index, modulo lets us start at 0 again
                    menu->selectedIndex = ((menu->selectedIndex - 1 + menu->itemCount) % menu->itemCount);
                    // set selected to true
                    menu->menuItems[menu->selectedIndex].isSelected = true;
                    break;
                case SDLK_RETURN:
                    
                    if(menu->selectedIndex == 2) {
                        state->currentState = GAME_QUIT;
                    }
                    if(menu->selectedIndex == 0) {
                        state->currentState = GAME_RUNNING;
                    }
                    if(menu->selectedIndex == 1) {
                        printf("currently selected index: %d\n", menu->selectedIndex);
                    }
                    break;
                
                default:
                    break;
            }
            break;

        
        default:
            break;
    }
}

void process_input(GameState *state) {
    SDL_Event event;


    while (SDL_PollEvent(&event)) {
        
        
        switch (event.type)
        {
        // the 'x' button is pressed
        // quit the game
        case SDL_QUIT:
            state->currentState = GAME_QUIT;
            break;
        
        case SDL_KEYDOWN:
             if (state->currentState == GAME_PAUSED) {
                process_main_menu_input(state, &event);
            }
            switch (event.key.keysym.sym)
            {
            // press escape for main menu
            case SDLK_ESCAPE:
                if(state->currentState == GAME_RUNNING) {
                    state->currentState = GAME_PAUSED;
                }
                else if(state->currentState == GAME_PAUSED)
                    state->currentState = GAME_RUNNING;
                break;
            
            default:
                break;
            }
        break;
        case SDL_MOUSEBUTTONDOWN:
            // we want to see if they click on the 'x' button while the game is paused
            // this needs to be changed because it should only be checked 
            // when the game is paused
            if (state->currentState == GAME_PAUSED) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    struct SDL_Point mousePoint = {
                        mousePoint.x = event.button.x,
                        mousePoint.y = event.button.y
                    };
                if (SDL_PointInRect(&mousePoint, &state->mainMenu.closeButtonRect)) {
                    state->currentState = GAME_RUNNING;
                }
                }
            }
            break;
        
        default:
            break;
        }
    }
}


int main(void) {
    GameState *state = malloc(sizeof(GameState));
    if (!state) {
        fprintf(stderr, "Failed to allocate game state\n");
        return 1;
    }

    // Initialize counts to 0
    state->texture_count = 0;
    

    // Initialize window and check result
    if (init_window(state) != GAME_RUNNING) {
        free(state);
        return 1;
    }

    init_main_menu(&state->mainMenu);

    state->player = malloc(sizeof(struct MainChar));
    init_player(state->player, 0.0,0.0,48,48);

    while(state->currentState != GAME_QUIT) {
        SDL_PumpEvents();
        process_input(state);
        render(state);
    }

    destroy_window(state);
    

    return 0;

}