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

void stealCard(GameState* game, int stealIdx, Card drawnCard);
int scoreCard(GameState* game, Card drawnCard);

void takeTurn(GameState* game, int playerAction);

int playGame(GameState* game);
int initGame();
int debugGame(DrawPile* drawPile, Player players[], int playerCount);

#endif
