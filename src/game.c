/**
 * @file  game.c
 * @brief Implementation of the game module.
 *
 * Defines the interface for the game module and provides internal
 * helper functions and data structures to initialize, interact with,
 * update, and delete the game state.
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
#include "input.h"     // for handling user input
#include "player.h"    // for the player module
#include "utils.h"     // for freeing pointers

struct GameContext {
    SDL_Window    *restrict window;            // the program window
    SDL_Renderer  *restrict renderer;          // the renderer for the window
    struct Player *restrict player;            // the user's in-game avatar
    bool                    isFullscreen : 1;  // is the game at full screen?
    bool                    isRunning    : 1;  // is the game currently running?
};


// === Static function prototypes === //

// Sets the context members to their default values, printing any errors
static bool setDefaultValues(struct GameContext *pGame, const char *title);

// Executes the user's requested actions one by one each frame
static void processGameActions(struct GameContext *restrict pGame);


// === Interface function definitions === //

/* Parses the command-line arguments, if any are given. Allocates and
 * initializes the data structures required for a playable game context.
 */
struct GameContext *game_initContext(int argc, char **argv, const char *title)
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

    struct GameContext *pGame = malloc(sizeof(*pGame));

    if (pGame)
    {
        if (!setDefaultValues(pGame, title))  // ensure setting values succeeds
        {
            freeMemory((void **)&pGame);      // sets pGame back to to NULL
        }
    }
    else
    {
        perror("Error: Unable to allocate a game context");
    }

    return pGame;
}


/* Continuously calls the functions required to play, update, and render
 * the game. The loop ends when the user enters the right inputs to
 * terminate the game.
 */
void game_runMainLoop(struct GameContext *restrict pGame)
{
    input_clearEventQueue();  // start with a blank events slate

    // Run the main loop
    while (pGame->isRunning)
    {
        // React to the user's input
        input_refreshActions();
        processGameActions(pGame);

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
}


/* Deallocates every bit of memory allocated for the game and nullifies
 * all pointers to that memory.
 */
void game_destroy(struct GameContext * restrict *ppGame)
{
    SDL_DestroyRenderer((*ppGame)->renderer);
    (*ppGame)->renderer = NULL;

    SDL_DestroyWindow((*ppGame)->window);
    (*ppGame)->window = NULL;

    SDL_Quit();
    freeMemory((void **)ppGame);
}


// === Static function definitions === //

/* Specifies sensible intial values for a brand-new game context. Also
 * sets the window title to the title string passed in.
 *
 * In case of failing to initialize any value, it prints its own error
 * message to specify which one did, stopping after the first failure
 * and freeing any members allocated up to that point.
 *
 * Can also be used to reset the game context values to their defaults
 * after modifying them.
 */
static bool setDefaultValues(struct GameContext *pGame, const char *title)
{
    assert(pGame != NULL);

    pGame->isFullscreen = false;
    SDL_WindowFlags windowFlags
        = (SDL_WINDOW_FULLSCREEN * pGame->isFullscreen)
        |  SDL_WINDOW_KEYBOARD_GRABBED;

    // Allocate a window
    pGame->window = SDL_CreateWindow(title, 1280, 720, windowFlags);

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

    // Allocate the player
    pGame->player = player_init(32.0, 64.0, 0.0, -1.0);

    if (!pGame->player)
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize a player: %s.",
            SDL_GetError()
        );
        free(pGame->renderer);  // free first to avoid a dangling window pointer
        free(pGame->window);
        return false;
    }

    pGame->isRunning = true;  // and we're on
    return true;
}


/* Converts the abstract actions in the input module's action queue into
 * concrete in-game actions.
 */
static void processGameActions(struct GameContext *restrict pGame)
{
    struct GameAction action;
    while (input_loadNextAction(&action))
    {
        switch (action.command)
        {
        case COMMAND_TOGGLE_FULLSCR:
            pGame->isFullscreen = !pGame->isFullscreen;
            SDL_SetWindowFullscreen(pGame->window, pGame->isFullscreen);
            break;
        case COMMAND_QUIT:
            pGame->isRunning = false;
            break;
        }
    }
}
