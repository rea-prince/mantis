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

// Load players function

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

// Display winner

// Edit and re-sort players.txt


/* TO-DO */

// Player turn

// Check player win

// Round simulation

// Game simulation

int playGame(Card* gameDeck, Player* players) {
    /* Game proper */

    // state vars for game condition
        // win bool
        // winner placeholder struct

    // initialize deck (randomized)

    // ROUND simulation loops while condition is not met
    return 1;
}

// Initialize game

int initGame() {

    /* Game variables */

    int playerCount, playerIdx;
    Card gameDeck[DECK_SIZE];

    // Load players.txt
    FILE* playersRead = fopen("players.txt", "r");
    if (playersRead == NULL)
        printf("Error: Could not read from players.txt\n");

    // start players

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
            playerIdx++;
        }
    } while (playerIdx < playerCount);


    // open players.txt


    FILE* playersWrite = fopen("players.txt", "w");
    if (playersWrite == NULL)
        printf("Error: Could not write to players.txt\n");



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
    }

    /* Play Game */

    playGame(gameDeck, players);

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
