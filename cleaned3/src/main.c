#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

#define MAX_TEXTURES 50
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600



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

struct MainMenu {
    SDL_Rect rect;
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
    state->window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, 0);
    
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

    /// main pause menu and it's items
    state->textures[2] = IMG_LoadTexture(state->renderer, "pause_menu.png");
    state->texture_count++;
    if (!state->textures[2]) {
        fprintf(stderr, "IMG_LoadTexture Error pause_menu.png: %s\n", IMG_GetError());
        return false;
    }

    state->textures[3] = IMG_LoadTexture(state->renderer, "x_button.png");
    state->texture_count++;
    if (!state->textures[3]) {
        fprintf(stderr, "IMG_LoadTexture Error x_button.png: %s\n", IMG_GetError());
        return false;
    }



    state->currentState = GAME_RUNNING;
    return GAME_RUNNING;
}

void init_player(struct MainChar *player, float x, float y, int width, int height) {
    player->x = x;
    player->y = y;
    player->rect = (SDL_Rect){(int)x, (int)y, width, height};
}

void render(GameState *state) {
    SDL_RenderClear(state->renderer);
    // render main map
    SDL_RenderCopy(state->renderer,state->textures[0], NULL, NULL);
    // here we are rendering the main character and it's rect
    SDL_RenderCopy(state->renderer,state->textures[1], NULL, &state->player->rect);

    // render the main pause menu
    if (state->currentState == GAME_PAUSED) {
        SDL_RenderCopy(state->renderer, state->textures[2], NULL, NULL);

        SDL_Rect close_button = {768, 0, 32, 32};
        SDL_RenderCopy(state->renderer,state->textures[3], NULL, &close_button);
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
    free(state);
    SDL_Quit();
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
            switch (event.key.keysym.sym)
            {
            // press escape for main menu
            case SDLK_ESCAPE:
                if(state->currentState == GAME_RUNNING)
                    state->currentState = GAME_PAUSED;
                else if(state->currentState == GAME_PAUSED)
                    state->currentState = GAME_RUNNING;
                break;
            
            default:
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            break;
        
        default:
            break;
        }
    }
}


int main(void) {
    GameState* state = malloc(sizeof(GameState));
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