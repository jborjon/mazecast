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
 * @brief Initializes a game context.
 *
 * @param argc Number of command-line arguments from main(), if any.
 * @param argv List of command-line arguments from main(); can be null.
 * @return     Did the game initialize successfully?
 */
struct GameContext * game_initContext(int argc, char **argv);


/**
 * @brief Starts and runs the main game loop until an exit condition is met.
 */
void game_runMainLoop(struct GameContext *restrict pGame);


/**
 * @brief Cleans up memory after a game; only call it after game_runMainLoop().
 */
void game_destroy(struct GameContext **ppGame);

#endif  // GAME_H
