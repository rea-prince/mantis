/******************************************************************************
 *  Description     : A header file including all structs pertinent to the project
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

 #ifndef MODELS_H
 #define MODELS_H

 #define BACK_COLORS 3
 #define MAX_PLAYER_CARDS 6

/**
 * Enum for the card colors to make indexing easier
 */

/**
 * Template for the cards that will to be loaded from mantis.txt
 */
typedef struct {
    char color;             // card's color
    char back[BACK_COLORS]; // colors at the card's back
    int value;                        // card's color
} Card;

/**
 * Template for a player
 */
typedef struct {
    char* username;
    Card cards[MAX_PLAYER_CARDS];
    int points;
} Player;


#endif
