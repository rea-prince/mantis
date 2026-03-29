/******************************************************************************
 *  Description     : Headers for helper.c
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#ifndef HELPERS_H
#define HELPERS_H

/* CARD COLOR UTILITY */

enum Color matchColor(char c);
char matchColorChar(enum Color c);

/* USER INPUT */

void getInput(int *inputDest, int min, int max, int exclude);

/* DECK CONTROL */

Card drawCard(DrawPile* drawPile);
void createDeck(FILE* mantisDeck, GameState* game);
void populateDeck(DrawPile* drawPile, TankPile* tankPile);
int computePlayerScore(TankPile tankPile);

/* DATA SORTING */

void sortPlayersByPoints(Player players[], int numPlayers);
void sortPlayersByScore(PlayerRecord playerRecords[], int numPlayers);
void sortPlayersByWins(PlayerRecord playerRecords[], int numPlayers);

/* DATA PERSISTENCE */

void loadPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords);
void savePlayerRecords(PlayerRecord playerRecords[], int numPlayerRecords);

#endif
