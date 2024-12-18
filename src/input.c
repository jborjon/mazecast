/**
 * @file  input.c
 * @brief Implementation of the input module.
 * 
 * Defines the interface for the input module and provides internal
 * helper functions 
 * 
 * @author Joseph Borjon
 * @date   2024-12-16
 */

#include "input.h"  // the header implemented here

struct UserInput
{
    int   keyboardState;  // bit field of keys pressed/not pressed
    float xMouseMotion;   // the relative x motion of the mouse
    float yMouseMotion;   // the relative y motion of the mouse
};
