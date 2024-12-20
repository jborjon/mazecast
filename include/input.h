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

#include <SDL3/SDL.h>  // for SDL3

/**
 * @brief The game actions the user can perform through input devices.
 *
 * Each enumerator represents exactly one action from the user's input
 * devices that should be converted into an in-game action or ignored,
 * as determined by the current game state.
 */
enum UserAction
{
    ACTION_TOGGLE_FULLSCREEN,
    ACTION_QUIT,
    NUM_ACTIONS
};


/**
 * @brief Returns the next user command in the command queue or NULL if none.
 * @return The next user command to process, or NULL if the queue is empty.
 */
enum UserAction input_getNextAction(void);

#endif  // INPUT_H
