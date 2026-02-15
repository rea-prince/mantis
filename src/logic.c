/******************************************************************************
 *  Description     : Functions necessary for performing game logic
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_C // Include this to prevent redefinition error
#define LOGIC_C // Include this to prevent redefinition error

#include "common.h"
#include "models.h"
#include "helpers.h"

/* TO-DO */

/* -------------------- */
/* SIMULATE PLAYER TURN */
// take players array, deck array, turn index, player action
// If steal,
// If score,





/* -------------- */
/* SIMULATE ROUND */

// Loop through players
// Call playerTurn()






/* ------------- */
/* SIMULATE GAME */

int playGame(Card* gameDeck, Player* players) {


    // state vars for game condition
        // win bool
        // winner placeholder struct

    // initialize deck (randomized)

    // ROUND simulation loops while condition is not met
    return 1;
}

/* --------------- */
/* INITIALIZE GAME */

int initGame() {

    int playerCount, playerIdx;
    Card gameDeck[DECK_SIZE];

    /* INITIALIZE PLAYERS */

    printf("How many players? : ");
    scanf("%d", &playerCount);
    Player players[playerCount];

    char nameBuffer[MAX_NAME_CHARS];

    playerIdx = 0;
    do {
        printf("P%d : ", (playerIdx + 1));
        scanf("%s", nameBuffer);
        bool duplicateFound = 0;

        /*** TEMPORARY ***/
        // check for duplicates
        for (int name = 0; name < playerIdx; name++) {
            if (strcmp(players[name].username, nameBuffer) == 0) {
                printf("Error: Name already listed; please try another name\n");
                duplicateFound = 1;
            }
        }
        if (!duplicateFound) {
            strcpy(players[playerIdx].username, nameBuffer);
            players[playerIdx].points = 0;
            playerIdx++;
        }
    } while (playerIdx < playerCount);

    /* LOAD DECK */

    FILE* mantisDeck = fopen("mantis.txt", "r");
    if (mantisDeck == NULL)
        printf("Error: Could not load cards\n");
    else {
        createDeck(mantisDeck, gameDeck);
        fclose(mantisDeck);
    }

    /* PLAY GAME */

    playGame(gameDeck, players);

    // Display winner/loser

    /* LOG PLAYER STATS */

    // open players.txt

    FILE* playersRead = fopen("players.txt", "r");
    if (playersRead == NULL)
        printf("Error: Could not read from players.txt\n");
    FILE* playersWrite = fopen("players.txt", "w");
    if (playersWrite == NULL)
        printf("Error: Could not write to players.txt\n");

    // append names if non existent

    // edit scores

    // re-sort players.txt by high score

    // close players.txt
    fclose(playersRead);
    fclose(playersWrite);

    return 1; // return for success
}


#endif // LOGIC_C; Include this to prevent redefinition error
