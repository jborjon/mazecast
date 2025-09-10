/**
 * @file  input.h
 * @brief Header for the input module, which handles user input.
 *
 * Declares the interface for the input module. Defines concrete in-game
 * actions based on the set of current user inputs, and enables the
 * caller to get those discrete actions from an internal queue one by
 * one without worrying about what the specific physical inputs
 * (keypresses, mouse clicks, etc.) were.
 *
 * @author Joseph Borjon
 * @date   2024-12-16
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>   // for the bool type
#include <SDL3/SDL.h>  // for SDL3

/**
 * @brief The commands the user can input through interaction with devices.
 *
 * Each enumerator represents exactly one command from the user's input
 * devices that should be converted into an in-game action or ignored,
 * as determined by the current game state.
 */
enum UserCommand
{
    CMD_UNKNOWN,            ///< unknown command
    CMD_TOGGLE_FULLSCREEN,  ///< toggle between full and windowed screen
    CMD_QUIT,               ///< exit the game loop
    NUM_COMMANDS            ///< total number of commands
};

/**
 * @brief An action the game can execute based on a user's input command.
 *
 * You should consider this struct read-only. You may access its members
 * directly for read convenience and efficiency, but let the interface
 * functions modify them.
 */
struct GameAction
{
    enum UserCommand command;    ///< what the user wants done based on input
    float            magnitude;  ///< relative mouse motion, or 0 if a keypress
};


/**
 * @brief Clears all pending events currently in the SDL event queue.
 *
 * Useful for dropping any unneeded pending events right before starting
 * the main loop and right after transitioning game states.
 */
void input_clearEventQueue(void);


/**
 * @brief Fills the action queue with all the pending user commands.
 *
 * Should be called once every iteration of the main loop, immediately
 * before the loop that calls `input_loadNextAction`.
 */
void input_refreshActions(void);


/**
 * @brief Copies the next game action in the queue into the action passed in.
 * @return True for as long as actions remain in the queue; false when done.
 *
 * Loads the next unprocessed action in the queue into the pointed-to
 * action passed in. Then it advances the action queue to point to the
 * next queued action, ready for the next time the function is invoked
 * so that no additional interfacing is required between subsequent
 * calls.
 * 
 * Should be called in a loop that executes each action one by one until
 * no actions are left. This loop should start only after having called
 * `input_refreshActions` once within the main loop.
 */
bool input_loadNextAction(struct GameAction *restrict pAction);

#endif  // INPUT_H
