/**
 * @file  game.h
 * @brief Header for the game module.
 * 
 * Declares the interface for the game module. Enables the caller to initialize
 * a game, run its main loop until the player exits, and clean up the memory
 * after exiting.
 * 
 * @author Joseph Borjon
 * @date   2024-12-10
 */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>  // for the bool type


/**
 * @brief      Initializes a game context.
 * 
 * @param argc The number of command-line arguments from main(), if any.
 * @param argv The list of command-line arguments from main(); can be null.
 * @return     Did the game initialize successfully?
 */
bool game_init(int argc, char **argv);


/**
 * @brief Starts and runs the main game loop until an exit condition is met.
 */
void game_runMainLoop(void);


/**
 * @brief Cleans up memory after a game; only call it after game_runMainLoop().
 */
void game_cleanUp(void);

#endif  // GAME_H
