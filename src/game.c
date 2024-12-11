/**
 * @file  game.c
 * @brief Implementation of the game module.
 * 
 * Defines the interface for the game module and provides internal functions and
 * data structures to create, interact with, update, and delete the game state.
 * 
 * @author Joseph Borjon
 * @date   2024-12-10
 */

#include <stdio.h>    // for console I/O
#include <stdbool.h>  // for the bool type
#include "game.h"     // the header implemented here


/**
 * Allocates and initializes the data structures required for a playable game
 * context.
 */
bool game_init(int argc, char **argv)
{
    puts("In game_init()!");
    return true;
}


/**
 * Continuously calls the functions required to play, update, and render the
 * game. The loop ends when the user enters the right inputs to terminate the
 * game.
 */
void game_runMainLoop(void)
{
    puts("In game_runMainLoop()!");
    return;
}


/**
 * Deallocates every bit of memory allocated for the game and nullifies all
 * pointers to that memory.
 */
void game_cleanUp(void)
{
    puts("In game_cleanUp()!");
    return;
}
