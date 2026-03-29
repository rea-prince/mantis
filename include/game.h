/******************************************************************************
 *  Description     : Game logic headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#ifndef LOGIC_H
#define LOGIC_H

/* CORE MECHANICS */

void stealCard(GameState* game, int stealIdx, Card drawnCard);
void scoreCard(GameState* game, Card drawnCard);
void takeTurn(GameState* game);

/* GAME START */

void playGame(GameState* game);

#endif
