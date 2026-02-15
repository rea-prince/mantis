/******************************************************************************
 *  Description     : Functions necessary for performing game logic
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_C // Include this to prevent redefinition error
#define LOGIC_C // Include this to prevent redefinition error

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "rand.h"
#include "persistence.h"
#include "models.h"

#define DECK_SIZE 84
#define MAX_PLAYERS 4

/* HELPER FUNCTIONS */

// Load players function

// Load deck function from mantis.txt

int createDeck(FILE* mantisDeck, Card gameDeck[]) {

    char lineBuffer[11];
    int randSeed = randomInt();
    int valueBuffer;

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

// Display winner

// Edit and re-sort players.txt


/* TO-DO */

// Player turn

// Check player win

// Round simulation


// Game simulation (final loop)
int playGame() {
    /* Game variables */
    Card gameDeck[DECK_SIZE];
    Player players[MAX_PLAYERS];

    /* Loading players */
    // open players.txt
    FILE* playersRead = fopen("players.txt", "r");
    FILE* playersWrite = fopen("players.txt", "w");
    if (playersRead == NULL || playersWrite == NULL)
        printf("Error: Could not load players\n");

    // get number of players


    // for (number of players)
        // scanf for name
        // add and initialize to players array
        // if name not in players.txt,
            // append and initialize 0 0 for won and high score
        // else do nothing

    /* Loading deck */

    FILE* mantisDeck = fopen("mantis.txt", "r");
    if (mantisDeck == NULL)
        printf("Error: Could not load cards\n");
    else {
        createDeck(mantisDeck, gameDeck);
        fclose(mantisDeck);

        /* FOR DEBUGGING CARD LOADING
        for (int j = 0; j < DECK_SIZE; j++) {
            printf("color : %c\nback : %c %c %c\nvalue : %d\n -----\n",
                    gameDeck[j].color, gameDeck[j].back[0],
                    gameDeck[j].back[1], gameDeck[j].back[2],
                    gameDeck[j].value);
        }
        */
    }



    /* Game proper */

    // state vars for game condition
        // win bool
        // winner placeholder struct

    // initialize deck (randomized)

    // ROUND simulation loops while condition is not met

    /* Game end */

    // Display winner/loser

    // edit player wins, check if high score

    // re-sort players.txt by high score

    // close players.txt
    fclose(playersRead);
    fclose(playersWrite);

    return 1; // return for success
}



#endif // LOGIC_C; Include this to prevent redefinition error
