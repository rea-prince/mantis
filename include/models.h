/******************************************************************************
 *  Description     : A header file including all structs pertinent to the project
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef MODELS_H
#define MODELS_H

#include "common.h"

/**
 * Template for the cards that will to be loaded from mantis.txt
 */
typedef struct {
    char color;             // card's color
    char back[BACK_COLORS]; // colors at the card's back
    int value;              // card's color
} Card;

/**
 * Template for a player
 */
typedef struct {
    char* username;
    Card cards[CARD_COLORS + 1][CARDS_PER_COLOR]; // 7 colors and 1 score pile
    int points;
} Player;


#endif
