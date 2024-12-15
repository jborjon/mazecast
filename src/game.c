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
#include <stdlib.h>    // for the C standard library
#include <stdbool.h>   // for the bool type
#include <assert.h>    // for debugging assertions
#include <SDL3/SDL.h>  // for SDL3
#include "game.h"      // the header implemented here
#include "utils.h"     // for freeing memory

#define IS_FULLSCREEN_DEFAULT  false

struct GameContext {
    SDL_Window   *restrict window;            ///< the program window
    SDL_Renderer *restrict renderer;          ///< the renderer for the window
    bool                   isRunning    : 1;  ///< is the game running?
    bool                   isFullscreen : 1;  ///< is the game full screen?
};


// === Static function prototypes === //

// Sets the context members to their default values, printing any errors.
static bool setDefaultValues(struct GameContext *restrict pGame);


// === External function definitions === //

/**
 * Parses the command-line arguments, if any are given. Allocates and
 * initializes the data structures required for a playable game context.
 */
struct GameContext *game_initContext(int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))  // implies event init too
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "SDL3 failed to initialize: %s.",
            SDL_GetError()
        );
        return NULL;
    }

    struct GameContext *restrict pGame = malloc(sizeof(*pGame));

    if (pGame)
    {
        if (!setDefaultValues(pGame))  // make sure setting values succeeds
        {
            free(pGame);
            return NULL;
        }
    }
    else
    {
        perror("Error: Unable to allocate a game context");
        return NULL;
    }

    return pGame;
}


/**
 * Continuously calls the functions required to play, update, and render
 * the game. The loop ends when the user enters the right inputs to
 * terminate the game.
 */
void game_runMainLoop(struct GameContext *restrict pGame)
{
    SDL_Event event;
    pGame->isRunning = true;  // and we're on

    // Handle input events
    do
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key)
                {
                case SDLK_F:
                    pGame->isFullscreen = !pGame->isFullscreen;
                    SDL_SetWindowFullscreen(pGame->window, pGame->isFullscreen);
                    break;
                case SDLK_ESCAPE:
                    pGame->isRunning = false;
                    break;
                }
                break;
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
    SDL_DestroyRenderer((*ppGame)->renderer);
    (*ppGame)->renderer = NULL;

    SDL_DestroyWindow((*ppGame)->window);
    (*ppGame)->window = NULL;

    SDL_Quit();
    freeMemory((void *restrict*)ppGame);
}


// === Static function definitions === //

/*
 * Specifies sensible values for a brand-new game context; for example,
 * all the pointers are set to NULL.
 * 
 * In case of failing to initialize any value, it prints its own error
 * message to specify which one did, stopping after the first failure
 * and freeing any members allocated up to that point.
 * 
 * Can also be used to reset the game context values to their defaults
 * after modifying them.
 */
static bool setDefaultValues(struct GameContext *restrict pGame)
{
    assert(pGame != NULL);

    // Allocate a window
    pGame->window = SDL_CreateWindow("Mazecast", 1280, 720, 0);

    if (!pGame->window)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to create a window for the game: %s.",
            SDL_GetError()
        );
        return false;
    }

    // Allocate the window renderer
    pGame->renderer = SDL_CreateRenderer(pGame->window, NULL);

    if (!pGame->renderer)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize a renderer for the game window: %s.",
            SDL_GetError()
        );
        free(pGame->window);
        return false;
    }

    pGame->isRunning    = false;  // we're not running yet
    pGame->isFullscreen = false;

    return true;
}
