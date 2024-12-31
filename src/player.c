/**
 * @file  player.c
 * @brief Implementation of the player module.
 *
 * Defines the interface for the player module and provides internal
 * helper functions and data structures to initialize, update, and
 * delete the player state.
 * 
 * @date   2024-12-31
 */

#include <stdio.h>     // for console I/O
#include <stdlib.h>    // for the C standard library
#include <stdbool.h>   // for the bool type
#include <assert.h>    // for debugging assertions
#include "player.h"    // the header implemented here

struct Player {
    // Define player properties here
};


// === Static function prototypes === //

// Sets the player members to their default values, printing any errors
static bool setDefaultValues(struct Player *pPlayer);


// === Interface function definitions === //

/* Allocates and initializes the data structures required for a playable player context.
 */
struct Player *player_init(void)
{
    struct Player *pPlayer = malloc(sizeof(*pPlayer));

    if (pPlayer)
    {
        if (!setDefaultValues(pPlayer))  // ensure setting values succeeds
        {
            free(pPlayer);  // free memory if initialization fails
            pPlayer = NULL;
        }
    }
    else
    {
        perror("Error: Unable to allocate a player context");
    }

    return pPlayer;
}


/* Updates the player state based on game events.
 */
void player_update(struct Player *restrict pPlayer)
{
    // Update player state here
}


/* Deallocates every bit of memory allocated for the player and nullifies
 * all pointers to that memory.
 */
void player_destroy(struct Player *restrict *ppPlayer)
{
    if (ppPlayer && *ppPlayer)
    {
        free(*ppPlayer);
        *ppPlayer = NULL;
    }
}


// === Static function definitions === //

/* Specifies sensible values for a brand-new player context; for example,
 * all the pointers are set to `NULL`.
 *
 * In case of failing to initialize any value, it prints its own error
 * message to specify which one did, stopping after the first failure
 * and freeing any members allocated up to that point.
 *
 * Can also be used to reset the player context values to their defaults
 * after modifying them.
 */
static bool setDefaultValues(struct Player *pPlayer)
{
    assert(pPlayer != NULL);

    // Initialize player properties to default values here

    return true;
}
