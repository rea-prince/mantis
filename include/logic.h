/******************************************************************************
 *  Description     : Game logic headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_H // Include this to prevent redefinition error
#define LOGIC_H // Include this to prevent redefinition error

#include "common.h"
#include "models.h"

int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount);
int createDeck(FILE* mantisDeck, Card gameDeck[]);

int initGame();
int playGame();

#endif // HELPERS_1_C; Include this to prevent redefinition error
