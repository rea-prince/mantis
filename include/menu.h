/******************************************************************************
 *  Description     : Game menu headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#ifndef MENU_H
#define MENU_H

/* MENU OPTIONS */

void newGame(GameState* game, PlayerRecord playerRecords[MAX_LOGGED_PLAYERS], int *numPlayerRecords);
void topPlayers(PlayerRecord playerRecords[MAX_LOGGED_PLAYERS], int numPlayers);
void gameSettings(GameState *game);

#endif
