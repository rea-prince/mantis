/******************************************************************************
 *  Description     : Display function headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

void displayCustomBox(char* strInput);

/* MENU DISPLAYS */

void displayMenuTopPlayers();
void displayMenuGameSettings();
void displayMenuMain();
void displayTopPlayers(PlayerRecord playerRecords[], int numPlayers);

/* PLAYER CREATION DISPLAYS */

void displayPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords, int playerIdx);
void displayPlayerUsernames(GameState* game, int playerIdx);

/* GAMEPLAY DISPLAYS */

void displayBackCards(GameState* game);
void displayTurn(GameState* game, int* playerAction);
void displayTurnInfo(GameState* game, int* playerAction);
void displayEndTurn(GameState* game);

/* DEBUG DISPLAYS */

void displayCards(DrawPile* drawPile);
void displayPlayerCards(DrawPile* drawPile, Player players[], int numPlayers);

#endif
