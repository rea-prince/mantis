/******************************************************************************
 *  Description     : A header file including all structs pertinent to the project
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef MODELS_H
#define MODELS_H

#include "common.h"

enum Color {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    INDIGO,
    VIOLET
};

/**
 * Template for the cards that will to be loaded from mantis.txt
 */
typedef struct {
    enum Color color;             // card's color
    enum Color back[BACK_COLORS]; // colors at the card's back
    int value;              // card's color
} Card;

typedef struct {
    Card cards[CARD_COLORS + 1][CARDS_PER_COLOR]; // 7 colors and 1 score pile
    int cardsPerColor[CARD_COLORS];
    int totalCards;
} TankPile;

typedef struct {
    Card cards[DECK_SIZE];
    int totalCards;
} DrawPile;

/**
 * Template for a player
 */
typedef struct {
    char username[MAX_NAME_CHARS];
    TankPile tankPile;
    int points;
} Player;


#endif
