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

int stealCard(Player players[], int playerIdx, int stealIdx, Card drawnCard);

int simulatePlayerTurn(Player players[], int playerTurn, DrawPile *drawPile, int playerAction);

int initGame();
int playGame();
int debugGame(DrawPile* drawPile, Player players[], int playerCount);

#endif
