/**
 * @file  player.c
 * @brief Implementation of the player module.
 *
 * Defines the interface for the player module and provides internal
 * helper functions and data structures to initialize, update, and
 * delete the player state.
 *
 * @author Joseph Borjon
 * @date   2024-12-31
 */

#include <stdio.h>   // for console I/O
#include <stdlib.h>  // for the C standard library
#include "player.h"  // the header implemented here
#include "utils.h"   // for freeing pointers

struct Player
{
    double xPos;    // player x-position in the game world
    double yPos;    // player y-position
    double xDir;    // player's facing direction in x
    double yDir;    // player's facing direction in y
    double xVel;    // how much to move in x
    double yVel;    // how much to move in y
    double radius;  // half width and height in game units
};


// === Interface function definitions === //

/* Allocates and initializes the data structure and additional data
 * required for a player.
 */
struct Player *player_init(
    double startingXPos,
    double startingYPos,
    double startingXDir,
    double startingYDir
) {
    struct Player *pPlayer = malloc(sizeof(*pPlayer));

    if (!pPlayer)
    {
        perror("Error: Unable to allocate a new player");
        return NULL;
    }

    pPlayer->xPos   = startingXPos;
    pPlayer->yPos   = startingYPos;
    pPlayer->xDir   = startingXDir;
    pPlayer->yDir   = startingYDir;
    pPlayer->xVel   = 0.0;
    pPlayer->yVel   = 0.0;
    pPlayer->radius = 0.4;

    return pPlayer;
}


/* Updates the player state based on game actions, a.k.a. events.
 */
void player_update(struct Player *restrict pPlayer)
{
    // TODO: Update player state here
}


/* Deallocates every bit of memory allocated for the player and
 * nullifies all pointers to that memory.
 */
void player_destroy(struct Player *restrict *ppPlayer)
{
    freeMemory((void **)ppPlayer);
}
