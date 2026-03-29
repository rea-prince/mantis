/******************************************************************************
 *  Description     : Helper functions that don't make decisions for the game flow
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

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
        default: returnVal = N_INVALID_COLOR; break;
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
        case N_INVALID_COLOR: returnVal = 'R'; break; // default value
    }

    return returnVal;
}

void getInput(int *inputDest, int min, int max, int exclude) {
    StrList buffer;
    bool valid = false;

    while (!valid) {
        printf("\n+----+\n| >> | ");
        if (fgets(buffer, sizeof(buffer), stdin)) {

            // parse integer from the string buffer

            if (sscanf(buffer, "%d", inputDest) == 1) {
                if (*inputDest >= min && (*inputDest < max || max == -1) && (exclude == -1 || *inputDest != exclude)) {
                    valid = true;
                }
            }
        }
        printf("+----+\n");

        if (!valid) {
            printf("\nError! Please enter a valid input.\n");
        }
    }
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

    /* Load deck into memory */

    int cardIdx = 0;
    char f, b1, b2, b3;

    while (cardIdx < DECK_SIZE && fgets(lineBuffer, sizeof(lineBuffer), mantisDeck)) {
        sscanf(lineBuffer, "%c | %c %c %c %d",
            &f, &b1, &b2, &b3, &game->drawPile.cards[cardIdx].value
        );

        game->drawPile.cards[cardIdx].color = matchColor(f);

        game->drawPile.cards[cardIdx].back[0] = matchColor(b1);
        game->drawPile.cards[cardIdx].back[1] = matchColor(b2);
        game->drawPile.cards[cardIdx].back[2] = matchColor(b3);

        cardIdx++;
    }

    game->drawPile.totalCards = cardIdx;

    /* Shuffle deck */

    if (game->randSeed == -1) {
        randSeed = randomInt();
    } else {
        randSeed = game->randSeed;
    }

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
        ++tankPile->totalCards;
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

void sortPlayersByPoints(Player players[], int numPlayers) {

    // find player with most points

    int i, j;
    int max;

    Player tempPlayer;

    for (i = 0; i < numPlayers - 1; i++) {
        max = i;

        for (j = i + 1; j < numPlayers; j++) {
            if (players[j].points > players[max].points) {
                max = j;
            } else if (players[j].points == players[max].points) {
                if (players[j].tankPile.totalCards > players[max].tankPile.totalCards) {
                    max = j;
                }
            }

        }
        if (max != i) {
            tempPlayer = players[i];
            players[i] = players[max];
            players[max] = tempPlayer;
        }
    }
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
