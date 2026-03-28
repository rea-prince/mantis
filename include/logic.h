/******************************************************************************
 *  Description     : Game logic headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_H
#define LOGIC_H

/* CORE MECHANICS */

void stealCard(GameState* game, int stealIdx, Card drawnCard);
void scoreCard(GameState* game, Card drawnCard);
void takeTurn(GameState* game);

/* GAME START */

int playGame(GameState* game);
int debugGame(DrawPile* drawPile, Player players[MAX_PLAYERS], int playerCount);

/* MENU OPTIONS */

void newGame(GameState* game, PlayerRecord playerRecords[MAX_LOGGED_PLAYERS], int *numPlayerRecords);
void topPlayers(PlayerRecord playerRecords[MAX_LOGGED_PLAYERS], int numPlayers);
void gameSettings(GameState *game);

#endif
