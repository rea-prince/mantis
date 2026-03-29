/******************************************************************************
 *  Description     : Headers for helper.c
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_H
#define HELPERS_H

/* CARD COLOR UTILITY */

enum Color matchColor(char c);
char matchColorChar(enum Color c);

/* USER INPUT */
// TODO: merge all input into one function
void getGameInput(int* inputDest, enum Action act, GameState game);
void getMenuInput(int* inputDest);
void getTopPlayersInput (int *inputDest);
void getSettingsInput(int *inputDest);


/* DECK CONTROL */

Card drawCard(DrawPile* drawPile);
int createDeck(FILE* mantisDeck, GameState* game);
int populateDeck(DrawPile* drawPile, TankPile* tankPile);
int computePlayerScore(TankPile tankPile);

/* DATA PERSISTENCE */

void sortPlayersByPoints(Player players[], int numPlayers);
void sortPlayersByScore(PlayerRecord playerRecords[], int numPlayers);
void sortPlayersByWins(PlayerRecord playerRecords[], int numPlayers);
void loadPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords);
void savePlayerRecords(PlayerRecord playerRecords[], int numPlayerRecords);

#endif
