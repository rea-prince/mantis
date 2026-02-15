/******************************************************************************
 *  Description     : Game logic headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_H // Include this to prevent redefinition error
#define LOGIC_H // Include this to prevent redefinition error

void displayCoodinates(Coordinate points[], int arrSize);

int createDeck(FILE* mantisDeck, Card gameDeck[]);

int playGame();

#endif // HELPERS_1_C; Include this to prevent redefinition error
