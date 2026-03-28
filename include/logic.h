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
void scoreCard(GameState* game, Card drawnCard);

void takeTurn(GameState* game);

int playGame(GameState* game);
int debugGame(DrawPile* drawPile, Player players[], int playerCount);

GameState newGame();
void topPlayers(Player playerList[], int numPlayers);

#endif
