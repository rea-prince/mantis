/******************************************************************************
 *  Description     : Helper functions that don't make decisions for the game flow
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

// match enum to color (char)

char matchColorChar(enum Color c) {
    char returnVal;

    switch (c) {
        case RED: returnVal = 'R'; break;
        case ORANGE: returnVal = 'O'; break;
        case YELLOW: returnVal = 'Y'; break;
        case GREEN: returnVal = 'G'; break;
        case BLUE: returnVal = 'B';  break;
        case INDIGO: returnVal = 'I'; break;
        case VIOLET: returnVal = 'V'; break;
    }

    return returnVal;
}

// Search name function

int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount) {
    int nameIdx;
    int retIdx = -1;
    for (nameIdx = 0; nameIdx < playerCount && retIdx == -1; nameIdx++) {
        if (strcmp(list[nameIdx], key) == 0) {
            retIdx = nameIdx;
        }
    }

    return retIdx;
}

// Draw cards to populate a tank pile

int drawCardPopulate(DrawPile* drawPile, TankPile* tankPile) {

    /* Get top level card */

    enum Color topColorIdx = drawPile->cards[0].color;
    enum Color endCardIdx = tankPile->cardsPerColor[topColorIdx];

    /* Append to user cards */

    tankPile->cards[topColorIdx][endCardIdx] = drawPile->cards[0];
    ++tankPile->cardsPerColor[topColorIdx];

    /* Adjust drawPile */

    int i;
    for (i = 0; i < drawPile->totalCards - 1; i++) {
        drawPile->cards[i] = drawPile->cards[i + 1];
    }

    --drawPile->totalCards;

    return 1;
}

// Pick out a single card from the draw pile
//
Card drawCard(DrawPile* drawPile) {
    Card drawnCard = drawPile->cards[0];

    int i;
    for (i = 0; i < drawPile->totalCards - 1; i++) {
        drawPile->cards[i] = drawPile->cards[i + 1];
    }

    --drawPile->totalCards;

    return drawnCard;
}


// Load deck function from mantis.txt

int createDeck(FILE* mantisDeck, DrawPile* drawPile) {

    char lineBuffer[LINE_SIZE];
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


// Populate player deck

int populateDeck(DrawPile* drawPile, TankPile* tankPile) {

    /* Place cards into player tank pile */

    int i;
    for (i = 0; i < 4; i++) {
        drawCardPopulate(drawPile, tankPile);
    }

    return 1;
}

// Compute player score

int computePlayerScore(TankPile tankPile) {
    int i;
    int total = 0;

    for (i = 0; i < tankPile.cardsPerColor[SCORE_PILE_IDX]; i++) {
        total += tankPile.cards[SCORE_PILE_IDX][i].value;
    }

    return total;
}


// Edit and re-sort players.txt

#endif
