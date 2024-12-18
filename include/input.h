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

#ifndef INPUT_H
#define INPUT_H

/**
 * @brief The current state of the input devices, the keyboard and mouse.
 * 
 * Contains all the states of the keyboard keys (pressed or not) and
 * mouse motion data necessary for the program to take the actions
 * specified by the user at any given time.
 */
struct UserInput;

#endif  // INPUT_H
