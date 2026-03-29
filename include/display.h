/******************************************************************************
 *  Description     : Display function headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

void displayCustomBox(char* strInput);
void displayCustomHeader(char* header);

/* MENU DISPLAYS */

void displayInMenuTopPlayers(int* input);
void displayInMenuGameSettings(int* input);
void displayMenuMain();
void displayTopPlayers(PlayerRecord playerRecords[], int numPlayers);

/* PLAYER CREATION DISPLAYS */

void displayInReqPlayers(int* numPlayers);
void displayInPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords, int playerIdx, int* option);
void displayPlayerUsernames(GameState* game, int playerIdx);

/* GAME INFO DISPLAYS */

void displayBackCards(GameState* game);
void displayInTurnInfo(GameState* game, int* playerAction);
void displayEndTurn(GameState* game);

/* GAMEPLAY DISPLAYS */

void displayDrawnCard(Card drawnCard);
void displayScoreCard(GameState* game, int drawnColor, int totalPts, int totalWithDrawn, int playerIdx, int numPlayerCards);

void displayInStealOptions(GameState* game, int* stealCardIdx);
void displayStealCard(GameState* game, int drawnColor, int playerIdx, int stealIdx);

/* DEBUG DISPLAYS */

void displayCards(DrawPile* drawPile);
void displayPlayerCards(DrawPile* drawPile, Player players[], int numPlayers);

/* SETTINGS DISPLAYS */
void displayInSettingsWinningScore(int* input);
void displayInSettingsShuffleSeed(int* input);

#endif
