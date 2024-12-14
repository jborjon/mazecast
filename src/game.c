/**
 * @file  game.c
 * @brief Implementation of the game module.
 * 
 * Defines the interface for the game module and provides internal
 * functions and data structures to create, interact with, update, and
 * delete the game state.
 * 
 * @author Joseph Borjon
 * @date   2024-12-10
 */

#include <stdio.h>     // for console I/O
#include <stdlib.h>    // for malloc
#include <stdbool.h>   // for the bool type
#include <SDL3/SDL.h>  // for SDL3
#include "game.h"      // the header implemented here
#include "utils.h"     // for freeing memory

struct GameContext {
    SDL_Window   *restrict window;     ///< the program window
    SDL_Renderer *restrict renderer;   ///< the renderer for the window
    bool                   isRunning;  ///< is the game currently running?
};


/**
 * Parses the command-line arguments, if any are given. Allocates and
 * initializes the data structures required for a playable game context.
 */
struct GameContext *game_initContext(int argc, char **argv)
{
    puts("In game_initContext()!");  // TODO: remove

    if (!SDL_Init(SDL_INIT_VIDEO))  // implies event init too
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "SDL3 failed to initialize: %s",
            SDL_GetError()
        );
        return NULL;
    }

    struct GameContext *restrict pGame = malloc(sizeof(*pGame));

    if (!pGame)
    {
        perror("Unable to allocate a game context");
        return NULL;
    }

    pGame->window = SDL_CreateWindow("Mazecast", 1280, 720, 0);

    if (!pGame->window)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to create a window for the game: %s",
            SDL_GetError()
        );
        return NULL;
    }

    pGame->renderer = SDL_CreateRenderer(pGame->window, NULL);

    if (!pGame->renderer)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize a renderer for the game window: %s",
            SDL_GetError()
        );
        return NULL;
    }

    pGame->isRunning = false;  // we're not running yet
    return pGame;
}


/**
 * Continuously calls the functions required to play, update, and render
 * the game. The loop ends when the user enters the right inputs to
 * terminate the game.
 */
void game_runMainLoop(struct GameContext *restrict pGame)
{
    puts("In game_runMainLoop()!");  // TODO: remove

    SDL_Event event;
    pGame->isRunning = true;

    // Handle input events
    do
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key != SDLK_ESCAPE)
                {
                    break;  // fall through to quit unless escape is pressed
                }
            case SDL_EVENT_QUIT:
                pGame->isRunning = false;
                break;
            }
        }

        // Render to the window
        SDL_SetRenderDrawColor(
            pGame->renderer,
            0x00,
            0x80,
            0x80,
            SDL_ALPHA_OPAQUE
        );
        SDL_RenderClear(pGame->renderer);
        SDL_RenderPresent(pGame->renderer);
        SDL_Delay(16);
    }
    while (pGame->isRunning);
}


/**
 * Deallocates every bit of memory allocated for the game and nullifies
 * all pointers to that memory.
 */
void game_destroy(struct GameContext *restrict* ppGame)
{
    puts("In game_destroy()!");  // TODO: remove
    SDL_DestroyRenderer((*ppGame)->renderer);
    (*ppGame)->renderer = NULL;

    SDL_DestroyWindow((*ppGame)->window);
    (*ppGame)->window = NULL;

    freeMemory((void **)ppGame);
}
