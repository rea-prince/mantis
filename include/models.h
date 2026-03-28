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
    EXIT_ACTION, // filler for index 0
    SCORE,
    STEAL,
    N_ACTION_Y // flag for no action yet
};

enum MenuOptions {
    EXIT_MENU,
    NEW_GAME,
    TOP_PLAYERS,
    GAME_SETTINGS,
    N_MENU_Y // flag for max menu option
};

enum TopPlayerActions {
    EXIT_TOP_PLAYERS,
    SORT_BY_WINS,
    SORT_BY_SCORE,
    N_SORT_Y // flag for max menu option
};

typedef char StrName[MAX_NAME_CHARS];
typedef char StrList[WIN_SCORE_NAME];

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
    StrName username;
    int wins;
    int highScore;
} PlayerRecord;

typedef struct {
    // game variables
    int numPlayers;
    Player players[MAX_PLAYERS];
    DrawPile drawPile;

    // state of the game
    int rotations;
    int playerTurn;
    int winner;
    bool gameWon;
} GameState;


#endif
