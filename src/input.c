/**
 * @file  input.c
 * @brief Implementation of the input module.
 *
 * Defines the interface for the input module and provides internal
 * helper functions 
 *
 * @author Joseph Borjon
 * @date   2024-12-16
 */

#include <stdbool.h>    // for the bool type
#include <assert.h>     // for debugging assertions
#include <SDL3/SDL.h>   // for SDL3 events
#include "input.h"      // the header implemented here

#define MAX_ACTIONS 32  // the highest possible number of actions in the queue

// Container for the game actions to be executed
struct ActionQueue
{
    struct GameAction actions[MAX_ACTIONS];  // container for the actions
    int               size;                  // number of actions in the queue
    int               head;                  // index of the current action
};

// The action queue itself
static struct ActionQueue _actionQueue = {
    .actions = {},
    .size    = 0,
    .head    = 0
};


// === Static function prototypes === //

// Adds an action with the specified value to the end of the queue if not full
void appendGameAction(enum UserCommand command, float magnitude);


// === Interface function definitions === //

/* Reads all the events currently in SDL3's event queue and does nothing
 * with them, effectively discarding them.
 */
void input_clearEventQueue(void)
{
    SDL_Event discardedEvent;
    while (SDL_PollEvent(&discardedEvent))
        ;  // empty on purpose
}


/* Reads user device inputs, converts them to game actions, and puts the
 * actions in the action queue in FIFO order.
 */
void input_refreshActions(void)
{
    // To keep track of the two fullscreen-toggling keys
    static bool isFullscrKey1Down = false;
    static bool isFullscrKey2Down = false;

    // Reset the queue
    _actionQueue.size = 0;
    _actionQueue.head = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key)
            {
            case SDLK_LALT:  // fall through to catch either key
            case SDLK_RALT:
                isFullscrKey1Down = true;
                break;
            case SDLK_RETURN:
                isFullscrKey2Down = true;
                break;
            case SDLK_ESCAPE:
                appendGameAction(COMMAND_QUIT, 0.0);
                break;
            }

            // Toggle full screen
            if (isFullscrKey1Down && isFullscrKey2Down)
            {
                appendGameAction(COMMAND_TOGGLE_FULLSCR, 0.0);

                // Prevent repeated toggling until after the keys are released
                isFullscrKey1Down = false;
                isFullscrKey2Down = false;
            }
            break;  // SDL_EVENT_KEY_DOWN
        case SDL_EVENT_KEY_UP:
            switch (event.key.key)
            {
            case SDLK_LALT:  // fall through to catch either key
            case SDLK_RALT:
                isFullscrKey1Down = false;
                break;
            case SDLK_RETURN:
                isFullscrKey2Down = false;
                break;
            }
            break;  // SDL_EVENT_KEY_UP
        case SDL_EVENT_QUIT:
            appendGameAction(COMMAND_QUIT, 0.0);
            break;
        }
    }

    assert(_actionQueue.size <= MAX_ACTIONS);
}


/* TODO: Document
 */
bool input_loadNextAction(struct GameAction *restrict pAction)
{
    if (_actionQueue.head >= _actionQueue.size)  // at the end of the queue
    {
        return false;
    }

    assert(_actionQueue.head < _actionQueue.size);
    *pAction = _actionQueue.actions[_actionQueue.head++];

    return true;
}


// === Static function definitions === //

/* TODO: Document
 */
void appendGameAction(enum UserCommand command, float magnitude)
{
    if (_actionQueue.size < MAX_ACTIONS)
    {
        _actionQueue.actions[_actionQueue.size++] = (struct GameAction) {
            .command   = command,
            .magnitude = magnitude
        };
    }
}
