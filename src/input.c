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

#include <stdbool.h>   // for the bool type
#include <SDL3/SDL.h>  // for SDL3
#include "input.h"     // the header implemented here

/* Contains all the states of the keyboard keys (pressed or not) and
 * mouse motion data necessary for the program to take the actions
 * specified by the user at any given time.
 */
struct UserCommand
{
    int   keyboardState;  // bit field of keys pressed/not pressed
    float xMouseMotion;   // the relative x motion of the mouse
    float yMouseMotion;   // the relative y motion of the mouse
};


/*
 * Reads user keyboard and mouse inputs. Always returns true unless the
 * user's input generates a quit event, so the return value can be used
 * to check whether the user has quit.
 */
enum UserAction input_getNextAction(void)
{
    // To keep track of the two fullscreen toggling keys
    static bool isFullscrKey1Down = false;
    static bool isFullscrKey2Down = false;

    bool isRunning = true;  // for the return value, not the loop below
    while (SDL_PollEvent(pEvent))
    {
        switch (pEvent->type)
        {
        case SDL_EVENT_KEY_DOWN:
            switch (pEvent->key.key)
            {
            case SDLK_LALT:    // fall through to catch either key
            case SDLK_RALT:
                isFullscrKey1Down = true;
                break;
            case SDLK_RETURN:
                isFullscrKey2Down = true;
                break;
            case SDLK_ESCAPE:  // quit the main loop
                isRunning = false;
                break;
            }

            // Toggle full screen
            if (isFullscrKey1Down && isFullscrKey2Down)
            {
                pGame->isFullscreen = !pGame->isFullscreen;
                SDL_SetWindowFullscreen(pGame->window, pGame->isFullscreen);

                // Prevent repeated toggling until after the keys are released
                isFullscrKey1Down = false;
                isFullscrKey2Down = false;
            }
            break;  // SDL_EVENT_KEY_DOWN
        case SDL_EVENT_KEY_UP:
            switch (pEvent->key.key)
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
            isRunning = false;
            break;
        }
    }

    return isRunning;
}
