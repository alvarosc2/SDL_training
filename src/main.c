// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

// Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
// Terminal font color
#define TERMINAL_GREEN 0, 255, 70

#define TERMINAL_FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
#define TERMINAL_FONT_SIZE 16
#define TERMINAL_MARGIN 10
#define TERMINAL_PANE_WIDTH 540
#define STEP_DELAY_MS 150

void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y)
{
    if (text[0] == '\0')
    {
        return;
    }

    SDL_Color green = {TERMINAL_GREEN, 255};
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, green);
    if (surface == NULL)
    {
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_FreeSurface(surface);

    if (texture != NULL)
    {
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_DestroyTexture(texture);
    }
}

int main(int argc, char *args[])
{
    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_Renderer *renderer = window ? SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) : NULL;
            TTF_Font *font = TTF_OpenFont(TERMINAL_FONT_PATH, TERMINAL_FONT_SIZE);

            // Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                draw_text(renderer, font, "Alvaro Silva Caballero", TERMINAL_MARGIN, 100);
                SDL_RenderPresent(renderer);
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}