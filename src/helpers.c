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

void getGameInput(int* inputDest, enum Action act, GameState game) {

    char enter;
    int scanfRet;

    bool valid = false;

    while (!valid) {

        printf(  "\n+----+\n");
        printf(    "| >> | ");
        scanfRet = scanf("%d", inputDest);
        printf(    "+----+\n");

        // > 0 because all provided options are 1-something;
        // input shall be reincremented outside the function

        if ( (scanfRet == 1 && *inputDest > EXIT_ACTION) && (
                    ((act == N_ACTION_Y) && (*inputDest < N_ACTION_Y)) ||
                    ((act == STEAL) && (*inputDest <= game.numPlayers) && (*inputDest != game.playerTurn + 1))
                )
            ) {
                // score, or (person is stealing, input is valid range of players, and not equal to self)
                valid = true;
        } else {
            printf("\nError! Please enter a valid input.\n");
            while (scanf("%c", &enter) == 1 && enter != '\n'); // flush
        }
    }

}

void getMenuInput(int* inputDest) {

    char enter;
    int scanfRet;

    bool valid = false;

    while (!valid) {

        printf(  "\n+----+\n");
        printf(    "| >> | ");
        scanfRet = scanf("%d", inputDest);
        printf(    "+----+\n");

        // > 0 because all provided options are 1-something;
        // input shall be reincremented outside the function

        if ( (scanfRet == 1 && *inputDest >= 0) && *inputDest < N_MENU_Y) {
            valid = true;
        } else {
            printf("\nError! Please enter a valid input.\n");
            while (scanf("%c", &enter) == 1 && enter != '\n'); // flush
        }
    }

}


void getTopPlayersInput (int *inputDest) {

    char enter;
    int scanfRet;

    bool valid = false;

    while (!valid) {

        printf(  "\n+----+\n");
        printf(    "| >> | ");
        scanfRet = scanf("%d", inputDest);
        printf(    "+----+\n");

        if ( (scanfRet == 1 && *inputDest >= 0) && *inputDest < N_SORT_Y) {
            valid = true;
        } else {
            printf("\nError! Please enter a valid input.\n");
            while (scanf("%c", &enter) == 1 && enter != '\n'); // flush
        }
    }
}

void getSettingsInput(int *inputDest) {

}

// Pick out a single card from the draw pile

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

int createDeck(FILE* mantisDeck, GameState* game) {

    char lineBuffer[LINE_SIZE];
    int randSeed;

    if (game->randSeed == -1) {
        randSeed = randomInt();
    } else {
        randSeed = game->randSeed;
    }

    // int randSeed = 999; // FOR UNIFORM TESTING

    /* Load deck into memory */

    int cardIdx = 0;
    while (cardIdx < DECK_SIZE && fgets(lineBuffer, sizeof(lineBuffer), mantisDeck)) {
        game->drawPile.cards[cardIdx].color = matchColor(lineBuffer[0]);

        game->drawPile.cards[cardIdx].back[0] = matchColor(lineBuffer[4]);
        game->drawPile.cards[cardIdx].back[1] = matchColor(lineBuffer[5]);
        game->drawPile.cards[cardIdx].back[2] = matchColor(lineBuffer[6]);

        game->drawPile.cards[cardIdx].value = (lineBuffer[8] - 48);
        cardIdx++;
    }

    game->drawPile.totalCards = cardIdx;

    /* Shuffle deck */

    shuffle(game->drawPile.cards, game->drawPile.totalCards, sizeof(Card), randSeed);

    return 1;
}


// Populate player deck

int populateDeck(DrawPile* drawPile, TankPile* tankPile) {

    /* Place cards into player tank pile */

    int i;
    for (i = 0; i < 4; i++) {
        Card drawnCard = drawCard(drawPile);
        int colorIdx = drawnCard.color;
        int numCards = tankPile->cardsPerColor[colorIdx];

        tankPile->cards[colorIdx][numCards] = drawnCard;
        ++tankPile->cardsPerColor[colorIdx];
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


void sortPlayersByWins(PlayerRecord playerRecords[], int numPlayers) {
    int i, j, max;
    PlayerRecord tempPlayer = {0};
    for (i = 0; i < numPlayers - 1; i++) {
        max = i;

        for (j = i + 1; j < numPlayers; j++) {
            if (playerRecords[j].wins > playerRecords[max].wins) {
                max = j;
            } else if (playerRecords[j].wins == playerRecords[max].wins) {
                if (strcmp(playerRecords[j].username, playerRecords[max].username) < 0) {
                    max = j;
                }
            }
        }

        if (max != i) {
            tempPlayer = playerRecords[i];
            playerRecords[i] = playerRecords[max];
            playerRecords[max] = tempPlayer;
        }
    }

}

void sortPlayersByScore(PlayerRecord playerRecords[], int numPlayers) {
    int i, j, max;
    PlayerRecord tempPlayer = {0};

    for (i = 0; i < numPlayers - 1; i++) {
        max = i;

        for (j = i + 1; j < numPlayers; j++) {
            if (playerRecords[j].highScore > playerRecords[max].highScore) {
                max = j;
            } else if (playerRecords[j].highScore == playerRecords[max].highScore) {
                if (strcmp(playerRecords[j].username, playerRecords[max].username) < 0) {
                    max = j;
                }
            }
        }

        if (max != i) {
            tempPlayer = playerRecords[i];
            playerRecords[i] = playerRecords[max];
            playerRecords[max] = tempPlayer;
        }
    }

}

void loadPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords) {

    StrList playersTxtBuffer;
    FILE* playersRead = fopen("players.txt", "r");

    if (playersRead == NULL) {
        printf("Error: Could not read from players.txt\n");
    } else {
        fgets(playersTxtBuffer, sizeof(playersTxtBuffer), playersRead);
        while (fgets(playersTxtBuffer, sizeof(playersTxtBuffer), playersRead)) {
            sscanf(playersTxtBuffer, " %d , %d , %s ",
                    &playerRecords[*numPlayerRecords].wins,
                    &playerRecords[*numPlayerRecords].highScore,
                    playerRecords[*numPlayerRecords].username
                );
            ++*numPlayerRecords;
        }
        fclose(playersRead);
    }
}

void savePlayerRecords(PlayerRecord playerRecords[], int numPlayerRecords) {
    int i;
    FILE* playersWrite = fopen("players.txt", "w");
    if (playersWrite == NULL) {
        printf("Error! There was an error in saving the player records.");
    } else {
        fprintf(playersWrite, "wins, highscore, username\n");
        for (i = 0; i < numPlayerRecords; i++) {
            fprintf(playersWrite, "%d, %d, %s\n",
                playerRecords[i].wins,
                playerRecords[i].highScore,
                playerRecords[i].username
            );
        }
        fclose(playersWrite);
    }
}


// Edit and re-sort players.txt

#endif
