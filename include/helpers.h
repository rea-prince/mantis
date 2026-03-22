/******************************************************************************
 *  Description     : Headers for helper.c
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_C
#define HELPERS_C


enum Color matchColor(char c);
char matchColorChar(enum Color c);

int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount);

Card drawCard(DrawPile* drawPile);
int createDeck(FILE* mantisDeck, DrawPile* drawPile);

int populateDeck(DrawPile* drawPile, TankPile* tankPile);

int computePlayerScore(TankPile tankPile);

void getInput(int* inputDest, enum Action act, GameState game);
void getMenuInput(int* inputDest);
void getTopPlayersInput (int *inputDest);
void getSettingsInput(int *inputDest);

#endif
