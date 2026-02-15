/******************************************************************************
 *  Description     : A header file including all structs pertinent to the project
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

 #ifndef MODELS_H
 #define MODELS_H

/**
 * Enum for the card colors to make indexing easier
 */
enum cardColor {
  R, O, Y, G, B, I, V
};

/**
 * Template for the cards that will to be loaded from mantis.txt
 */
typedef struct {
    enum cardColor color;   // card's color
    enum cardColor back[3]; // colors at the card's back
    int value;              // card's c
} Card;

/**
 * Template for a player
 */
typedef struct {
    char* username;
    Card cards[6];
    int points;
} Player;


#endif
