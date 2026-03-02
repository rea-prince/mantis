/******************************************************************************
 *  Description     : Headers for helper.c
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_C
#define HELPERS_C


enum Color matchColor(char c);
int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount);
int createDeck(FILE* mantisDeck, DrawPile* drawPile);

int drawCard(DrawPile* drawPile, TankPile* tankPile);
int populateDeck(DrawPile* drawPile, TankPile* tankPile);

#endif
