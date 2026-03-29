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
 *  Supported card colors in the game
 */

enum Color {
    RED = 0,
    ORANGE = 1,
    YELLOW = 2,
    GREEN = 3,
    BLUE = 4,
    INDIGO = 5,
    VIOLET = 6,
    N_INVALID_COLOR // flag for invalid color
};

/**
 *  Options for a player's turn action
 */

enum Action {
    EXIT_ACTION = 0,
    SCORE = 1,
    STEAL = 2,
    N_ACTION_Y // flag for max action option
};

/**
 *  Main menu navigation options
 */

enum MenuOptions {
    EXIT_MENU = 0,
    NEW_GAME = 1,
    TOP_PLAYERS = 2,
    GAME_SETTINGS = 3,
    N_MENU_Y // flag for max menu option
};

/**
 *  Sorting and display options for the Leaderboard
 */

enum MenuTopPlayerOptions {
    EXIT_TOP_PLAYERS,
    SORT_BY_WINS,
    SORT_BY_SCORE,
    SHOW_ALL,
    N_SORT_Y // flag for max menu option
};

/**
 *  Options for modifying game behavior and global state
 */

enum MenuGameSettingsOptions {
    EXIT_GAME_SETTINGS,
    SET_WINNING_SCORE,
    SET_SHUFFLE_SEED,
    TOGGLE_DEBUG_MODE,
    N_SET_Y // flag for max menu option
};

typedef char StrName[MAX_NAME_CHARS];
typedef char StrList[MAX_STR_LEN];

/**
 *  Template for the cards loaded from the external data file.
 *  Contains the front color, the three possible colors on the back,
 *  and the point value.
 */
typedef struct {
    enum Color color;             // card's front color
    enum Color back[BACK_COLORS]; // 3 colors shown on the card back
    int value;                    // point value (usually 1)
} Card;

/**
 *  Represents the collection of cards held by a player.
 *  Organizes cards by color for the 'Tank' and includes a designated
 *  score pile for banking points.
 */

typedef struct {
    Card cards[CARD_COLORS + 1][DECK_SIZE];
    int cardsPerColor[CARD_COLORS + 1]; // number of cards in each color/score slot
    int totalCards;                     // total count of all cards in the tank
} TankPile;

/**
 *  Represents the main deck from which players draw.
 */

typedef struct {
    Card cards[DECK_SIZE];
    int totalCards; // number of cards remaining in the deck
} DrawPile;

/**
 *  Template for an active player in the current game session.
 */

typedef struct {
    StrName username;
    TankPile tankPile;
    int points; // cumulative value of cards in the score pile
} Player;

/**
 *  Struct for storing player records
 */

typedef struct {
    StrName username;
    int wins;
    int highScore;
} PlayerRecord;

/**
 *  Central structure managing the current state of a game session,
 *  including player data, deck state, and configuration settings.
 */

typedef struct {
    // game variables
    int numPlayers;
    Player players[MAX_PLAYERS];
    DrawPile drawPile;

    // state of the game
    int playerTurn; // index of the player whose turn it is
    int winner;     // index of the winning player (-1 if multiple/draw)
    bool gameWon;   // flag indicating if the game has concluded

    // settings
    int randSeed;      // seed for random number generation
    int winningPoints; // score required to trigger a win
    bool debugMode;    // toggles visibility of the draw pile
} GameState;


#endif
