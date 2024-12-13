/**
 * @file  main.c
 * @brief Contains main(), the entry and exit point for the game.
 * 
 * Contains the main function of the program, which calls the procedures
 * to initialize a game context, run its main loop, and clean up the
 * memory after the game ends.
 * 
 * @author Joseph Borjon
 * @date   2024-12-10
 */

#include <stdio.h>          // for console I/O
#include <stdlib.h>         // for EXIT_FAILURE
#include <SDL3/SDL_main.h>  // for SDL3 to handle the program entry point
#include "game.h"           // for handling the game context


/**
 * @brief The program's main function.
 * 
 * @param argc Number of arguments passed from the command line, if any.
 * @param argv List of arguments passed from the command line, if any.
 * @return     Program exit code.
 * 
 * Neither the order nor the number of command-line arguments matters
 * as long as the arguments are valid. Invalid arguments will be ignored
 * after issuing a warning. The possible argument values, prefixed with
 * a dash, are:
 *   - windowed: Turn off fullscreen mode.
 *   - novsync : Turn off VSync.
 */
int main(int argc, char **argv)
{
    // Initialize the game
    struct GameContext *restrict pGame = game_initContext(argc, argv);

    if (!pGame)
    {
        perror("Aborting game due to initializion failure");
        return EXIT_FAILURE;
    }

    // Start the game loop and keep it going until the player exits
    game_runMainLoop(pGame);

    // Clean up
    game_destroy(&pGame);
    return 0;
}
