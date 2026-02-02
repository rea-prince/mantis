/******************************************************************************
 *  Description     : Functions necessary for performing game logic
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_C // Include this to prevent redefinition error
#define LOGIC_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "persistence.h"

/******************************************************************************
 * NOTE: These functions are placed here in helpers_1.c to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

/**
 * Displays the array of coordinates
 * @param points The array of coordinates to be displayed
 * @param arrSize The size of the array
 */
void displayCoodinates(Coordinate points[], int arrSize)
{
  // NOTE: This file includes defs.h, which provides access to the
  //       Coordinate structure definition.

  for (int i = 0; i < arrSize; i++)
    printf("(%d, %d)  ", points[i].x, points[i].y);

  printf("\n\n");
}


/* TODO */

// Player turn

// Round simulation

// Game simulation



#endif // HELPERS_1_C; Include this to prevent redefinition error
