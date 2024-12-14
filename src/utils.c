/**
 * @file  utils.c
 * @brief Implementation of the utils module.
 * 
 * Defines the interface for the utils module,
 * 
 * @author Joseph Borjon
 * @date   2024-12-13
 */

#include <stdlib.h>  // for the C standard library
#include <assert.h>  // for debugging assertions
#include "utils.h"   // the header implemented here


/**
 * Uses double indirection to set the value of the pointed-to pointer
 * equal to NULL after freeing it, without needing to nullify it outside
 * the function call.
 */
void freeMemory(void *restrict* ppData)
{
    assert(ppData != NULL);

    if (ppData && *ppData)
    {
        free(*ppData);
        *ppData = NULL;
    }

    assert(*ppData == NULL);
}
