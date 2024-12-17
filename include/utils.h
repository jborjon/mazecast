/**
 * @file  utils.h
 * @brief Header for utils, a set of common general-purpose functions.
 * 
 * Declares the interface for the utils module, which provides functions
 * for commonly performed operations.
 * 
 * @author Joseph Borjon
 * @date   2024-12-13
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Frees the pointed-to pointer and automatically sets its value to NULL.
 * @param ppData A pointer to the pointer being freed.
 */
void freeMemory(void *restrict* ppData);

#endif  // UTILS_H
