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

enum Action {
    SCORE,
    STEAL,
    N_ACTION_Y // flag for no action yet
};


typedef char StrName[MAX_NAME_CHARS];

/**
 * Template for the cards that will to be loaded from mantis.txt
 */
typedef struct {
    enum Color color;             // card's color
    enum Color back[BACK_COLORS]; // colors at the card's back
    int value;                    // card's points
} Card;

typedef struct {
    Card cards[CARD_COLORS + 1][CARDS_PER_COLOR]; // 7 colors and 1 score pile
    int cardsPerColor[CARD_COLORS + 1];
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
    StrName username;
    TankPile tankPile;
    int points;
} Player;

typedef struct {
    // game variables
    int numPlayers;
    Player players[MAX_PLAYERS];
    DrawPile drawPile;

    // state of the game
    int rotations;
    int playerTurn;
    bool gameWon;
    Player winner;
} GameState;


#endif
