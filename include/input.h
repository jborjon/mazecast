/**
 * @file  input.h
 * @brief Header for the input module, which handles user input.
 *
 * Declares the interface for the input module. Enables the caller to
 * get the state of the input devices pertinent to the actions available
 * in the game.
 *
 * @author Joseph Borjon
 * @date   2024-12-16
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>   // for the bool type
#include <SDL3/SDL.h>  // for SDL3

/**
 * @brief The current state of the input devices, the keyboard and mouse.
 *
 * Contains all the states of the keyboard keys (pressed or not) and
 * mouse motion data necessary for the program to take the actions
 * specified by the user at any given time.
 */
struct UserInput;


/**
 * @brief Reads user inputs, always returning true unless the user quits.
 *
 * @param pGame  The game context.
 * @param pEvent The SDL event to use for polling events.
 * @return       Always true unless the user's input generates a quit event.
 */
bool input_handleUserEvents(
    struct GameContext *restrict pGame,
    SDL_Event          *restrict pEvent
);

#endif  // INPUT_H
