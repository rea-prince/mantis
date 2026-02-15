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

int createDeck(FILE* mantisDeck, Card gameDeck[]) {

    char lineBuffer[11];
    int randSeed = randomInt();

    /* Load deck into memory */

    int cardIdx = 0;
    while (cardIdx < DECK_SIZE && fgets(lineBuffer, sizeof(lineBuffer), mantisDeck)) {
        gameDeck[cardIdx].color = lineBuffer[0];

        gameDeck[cardIdx].back[0] = lineBuffer[4];
        gameDeck[cardIdx].back[1] = lineBuffer[5];
        gameDeck[cardIdx].back[2] = lineBuffer[6];

        gameDeck[cardIdx].value = (lineBuffer[8] - 48);
        cardIdx++;
    }

    /* Shuffle deck */

    shuffle(gameDeck, cardIdx, sizeof(Card), randSeed);

    return 1;
}

// Edit and re-sort players.txt

#endif
