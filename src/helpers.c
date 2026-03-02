/******************************************************************************
 *  Description     : Helper functions to simplify logic.c
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_C
#define HELPERS_C

#include "common.h"
#include "models.h"

/* HELPER FUNCTIONS */

// Match char to color

enum Color matchColor(char c) {
    enum Color returnVal;
    switch (c) {
        case 'R': returnVal = RED; break;
        case 'O': returnVal = ORANGE; break;
        case 'Y': returnVal = YELLOW; break;
        case 'G': returnVal = GREEN; break;
        case 'B': returnVal = BLUE;  break;
        case 'I': returnVal = INDIGO; break;
        case 'V': returnVal = VIOLET; break;
    }

    return returnVal;
}

// Search name function

int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount) {
    int nameIdx;
    int retIdx = -1;
    for (nameIdx = 0; nameIdx < playerCount && retIdx == -1; nameIdx++)
        if (strcmp(list[nameIdx], key) == 0)
            retIdx = nameIdx;
    return retIdx;
}

// Load deck function from mantis.txt

int createDeck(FILE* mantisDeck, DrawPile* drawPile) {

    char lineBuffer[11];
    int randSeed = randomInt();

    /* Load deck into memory */

    int cardIdx = 0;
    while (cardIdx < DECK_SIZE && fgets(lineBuffer, sizeof(lineBuffer), mantisDeck)) {
        drawPile->cards[cardIdx].color = matchColor(lineBuffer[0]);

        drawPile->cards[cardIdx].back[0] = matchColor(lineBuffer[4]);
        drawPile->cards[cardIdx].back[1] = matchColor(lineBuffer[5]);
        drawPile->cards[cardIdx].back[2] = matchColor(lineBuffer[6]);

        drawPile->cards[cardIdx].value = (lineBuffer[8] - 48);
        cardIdx++;
    }

    drawPile->totalCards = cardIdx;

    /* Shuffle deck */

    shuffle(drawPile->cards, drawPile->totalCards, sizeof(Card), randSeed);

    return 1;
}

// Draw Card

int drawCard(DrawPile* drawPile, TankPile* tankPile) {

    /* Get top level card */

    int topColorIdx = drawPile->cards[0].color;
    int endCardIdx = tankPile->cardsPerColor[topColorIdx];

    /* Append to user cards */

    tankPile->cards[topColorIdx][endCardIdx] = drawPile->cards[0];
    ++tankPile->cardsPerColor[topColorIdx];

    /* Adjust drawPile */

    int i;
    for (i = 0; i < drawPile->totalCards - 1; i++)
        drawPile->cards[i] = drawPile->cards[i + 1];
    --drawPile->totalCards;

    return 1;
}

// Populate player deck

int populateDeck(DrawPile* drawPile, TankPile* tankPile) {

    /* Place cards into player tank pile */

    int i;
    for (i = 0; i < 4; i++)
        drawCard(drawPile, tankPile);

    return 1;
}

// Edit and re-sort players.txt

#endif
