/******************************************************************************
 *  Description     : Display function headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

/* DEBUG DISPLAYS */

void displayCards(DrawPile* drawPile);
void displayPlayerCards(DrawPile* drawPile, Player players[], int numPlayers);

/* GAMEPLAY DISPLAYS */

void displayBackCards(GameState* game);

/* MENU DISPLAYS */

#endif
