/******************************************************************************
 *  Description     : Functions necessary for performing game logic
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_C // Include this to prevent redefinition error
#define LOGIC_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdbool.h>
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

/* HELPER FUNCTIONS */

// Load players function

// Display winner

// Edit and re-sort players.txt


/* TO-DO */

// Player turn

// Check player win

// Round simulation

// Game simulation (final loop)

int playGame() {

    /* Loading players */

    // open players.txt

    // get number of players

    // for (number of players)
        // scanf for name
        // add and initialize to players array
        // if name not in players.txt,
            // append and initialize 0 0 for won and high score
        // else do nothing

    /* Game proper */

    // state vars for game condition
        // win bool
        // winner placeholder struct

    // ROUND simulation loops while condition is not met

    /* Game end */

    // Display winner/loser

    // edit player wins, check if high score

    // re-sort players.txt by high score

    // close players.txt

    return 1; // return for success
}



#endif // LOGIC_C; Include this to prevent redefinition error
