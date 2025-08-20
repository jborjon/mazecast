/**
 * @file  game.h
 * @brief Header for the game module, which handles core game logic.
 *
 * Declares the interface for the game module. Enables the caller to
 * initialize a game, run its main loop until the player exits, and
 * clean up the memory after exiting.
 *
 * @author Joseph Borjon
 * @date   2024-12-10
 */

#ifndef GAME_H
#define GAME_H

/**
 * @brief Container for all shared game properties.
 *
 * Contains all relevant game properties needed by the different
 * subsystems. Access and mutate its members through the functions
 * provided by the game module interface.
 */
struct GameContext;


/**
 * @brief Initializes a game context and returns a pointer to it.
 *
 * Prints its own error messages to indicate which part of the
 * initialization failed, if any. Always call this function before
 * running the main game loop; i.e., don't ever pass an uninitialized or
 * null pointer to game_runMainLoop.
 *
 * @param argc  Number of command-line arguments from main(), if any.
 * @param argv  List of command-line arguments from main(); can be null.
 * @param title Title of the game.
 * @return      Pointer to the just-initialized game context; `NULL` on failure.
 */
struct GameContext *game_initContext(int argc, char **argv, const char *title);


/**
 * @brief Starts and runs the main game loop until an exit condition is met.
 * @param pGame Pointer to the game context.
 */
void game_runMainLoop(struct GameContext *restrict pGame);


/**
 * @brief Cleans up memory once the game context is no longer needed.
 * @param ppGame Pointer to the game-context pointer.
 * 
 * Deallocates all memory used by the game context and sets the value of
 * the game-context pointer (pointed to by `ppGame`) to `NULL`.
 */
void game_destroy(struct GameContext * restrict *ppGame);

#endif  // GAME_H
