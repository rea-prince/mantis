/******************************************************************************
 *  Description     : Game logic headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_H
#define LOGIC_H

#include "common.h"
#include "models.h"

int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount);
int createDeck(FILE* mantisDeck, Card gameDeck[]);

int initGame();
int playGame();
int debugGame(DrawPile* drawPile, Player players[], int playerCount);

#endif
