/**
 * @file  player.h
 * @brief Header for the player module, which handles player-specific logic.
 *
 * Declares the interface for the player module. Enables the caller to
 * initialize a player, update player state, and clean up player-related
 * resources.
 * 
 * @author Joseph Borjon
 * @date   2024-12-31
 */

#ifndef PLAYER_H
#define PLAYER_H

/**
 * @brief Container for all player properties.
 *
 * Contains all relevant player properties needed by the different
 * subsystems. Access and mutate its members through the functions
 * provided by the player module interface.
 */
struct Player;


/**
 * @brief Initializes a player and returns a pointer to it.
 *
 * Prints its own error messages to indicate which part of the
 * initialization failed, if any. Always call this function before
 * running player-specific logic; i.e., don't ever pass an uninitialized
 * or null pointer to player-related functions.
 *
 * @return Pointer to the just-initialized player context; `NULL` on failure.
 */
struct Player *player_init(void);


/**
 * @brief Updates the player state based on game events.
 * @param pPlayer Pointer to the player context.
 */
void player_update(struct Player *restrict pPlayer);


/**
 * @brief Deallocates the player and sets the player pointer to `NULL`.
 * @param ppPlayer Pointer to the player-context pointer.
 */
void player_destroy(struct Player *restrict *ppPlayer);

#endif  // PLAYER_H
