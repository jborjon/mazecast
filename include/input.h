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

#include <stdint.h>  // for uint8_t

typedef uint8_t InputState;

InputState input_pollKeys(void);
