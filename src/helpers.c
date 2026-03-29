/******************************************************************************
 *  Description     : Helper functions that don't make decisions for the game flow
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#include "common.h"
#include "models.h"

/**
 *  Matches a character to its correct enum equivalent.
 *
 *  @param c Character to be matched
 *  @return returnVal The enum equivalent of the color that was matched
 *
 *  @pre c is a valid character that represents a number
 */

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
        default: returnVal = RED; break;
    }

    return returnVal;
}

/**
 *  Matches an enum value to its character equivalent
 *
 *  @param c Enum to be matched
 *  @return returnVal The character equivalent of the color that was matched
 *
 *  @pre c is a valid integer that matches a color
 */

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
        default: returnVal = 'R'; break; // default value
    }

    return returnVal;
}

/**
 *  Gets user input and restrains it according to min, max, and exclude.
 *  Ensures buffer is cleared after input is scanned.
 *
 *  @param inputDest Pointer to the input destination
 *  @param min Minimum number for input to be valid (inclusive)
 *  @param max Maximum value for input to be valid (exclusive)
 *  @param exclude Input to be excluded to be valid
 *  @return Void
 */

void getInput(int *inputDest, int min, int max, int exclude) {
    StrList buffer;
    bool valid = false;

    while (!valid) {
        printf("\n+----+\n| >> | ");

        if (fgets(buffer, sizeof(buffer), stdin)) {
            printf("+----+\n");

            // parse integer from the string buffer

            if (sscanf(buffer, "%d", inputDest) == 1) {
                if (*inputDest >= min && (*inputDest < max || max == -1) && (exclude == -1 || *inputDest != exclude)) {
                    valid = true;
                } else if (*inputDest < min) {
                    printf("\n\nError! Please enter a minimum of %d (inclusive)\n\n", min);
                } else if (*inputDest >= max) {
                    printf("\n\nError! Please enter a maximum of %d (exclusive)\n\n", max);
                } else if (*inputDest == exclude) {
                    printf("\n\nError! Please enter a value excluding %d\n\n", exclude);
                } else {
                    printf("\n\nError! Please enter a valid input.\n\n");
                }
            } else {
                printf("\n\nError! Please enter a valid integer input.\n\n");
            }
        } else {
            printf("\n\nError! Please provide an input.\n\n");
        }
    }
}

/**
 *  Draws the card at the top of the deck, adjusts each succeeding card into
 *  position, decrements the total cards in the draw pile, and returns the
 *  card that was drawn.
 *
 *  @param drawPile Pointer to the DrawPile to be drawn from
 *  @return drawnCard The card that was drawn from the pile
 *
 *  @pre drawPile points to an initialized DrawPile
 *  @pre drawPile->totalCards is > 0
 */

Card drawCard(DrawPile* drawPile) {
    Card drawnCard = {0};

    int i;

    if (drawPile->totalCards > 0) {
        drawnCard = drawPile->cards[0];

        for (i = 0; i < drawPile->totalCards - 1; i++) {
            drawPile->cards[i] = drawPile->cards[i + 1];
        }

        --drawPile->totalCards;
    }

    return drawnCard;
}

/**
 *  Loads cards from a file into the game's drawPile.
 *
 *  @param mantisDeck File pointer to the file containing card information
 *  @param game Pointer to the current game state struct
 *  @return Void
 *
 *  @pre mantisDeck is a valid file pointer != NULL
 *  @pre mantisDeck has at least 12 cards
 *  @pre game points to an initialized GameState
 */

void createDeck(FILE* mantisDeck, GameState* game) {

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
}

/**
 *  Populates the TankPile with cards drawn from the DrawPile.
 *
 *  @param drawPile Pointer to the DrawPile to draw cards from
 *  @param tankPile Pointer to the tankPile to put drawn cards into
 *  @return Void
 *
 *  @pre drawPile points to an initialized DrawPile with 84 cards
 *  @pre tankPile points to an empty TankPile
 */

void populateDeck(DrawPile* drawPile, TankPile* tankPile) {

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
}

// Compute player score

/**
 *  Sums the value of all cards from a given TankPile.
 *
 *  @param tankPile The TankPile to sum the points from
 *  @return total Total points of the given TankPile
 *
 *
 */

int computePlayerScore(TankPile tankPile) {
    int i;
    int total = 0;

    for (i = 0; i < tankPile.cardsPerColor[SCORE_PILE_IDX]; i++) {
        total += tankPile.cards[SCORE_PILE_IDX][i].value;
    }

    return total;
}

/**
 *  Sorts players according to total points and tank cards.
 *
 *  @param players[] Array of players to sort
 *  @param numPlayers Number of players in the array
 *  @return Void
 */

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

/**
 *  Sorts player records according to their total wins.
 *
 *  @param playerRecords[] Array of player records to sort
 *  @param numPlayers Number of players in the array
 *  @return Void
 */

void sortPlayersByWins(PlayerRecord playerRecords[], int numPlayers) {
    int i, j, max;
    PlayerRecord tempPlayer = {0};
    for (i = 0; i < numPlayers - 1; i++) {
        max = i;

        for (j = i + 1; j < numPlayers; j++) {
            if (playerRecords[j].wins > playerRecords[max].wins) {
                max = j;
            } else if (playerRecords[j].wins == playerRecords[max].wins) {
                if (playerRecords[j].highScore > playerRecords[max].highScore) {
                    max = j;
                } else if ((playerRecords[j].wins == playerRecords[max].wins) &&
                           (playerRecords[j].highScore == playerRecords[max].highScore)) {
                            if (strcmp(playerRecords[j].username, playerRecords[max].username) < 0) {
                                max = j;
                            }
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

/**
 *  Sorts player records according to their high scores.
 *
 *  @param playerRecords[] Array of player records to sort
 *  @param numPlayers Number of players in the array
 *  @return Void
 */

void sortPlayersByScore(PlayerRecord playerRecords[], int numPlayers) {
    int i, j, max;
    PlayerRecord tempPlayer = {0};

    for (i = 0; i < numPlayers - 1; i++) {
        max = i;

        for (j = i + 1; j < numPlayers; j++) {
            if (playerRecords[j].highScore > playerRecords[max].highScore) {
                max = j;
            } else if (playerRecords[j].highScore == playerRecords[max].highScore) {
                if (playerRecords[j].wins > playerRecords[max].wins) {
                    max = j;
                } else if ((playerRecords[j].highScore == playerRecords[max].highScore) &&
                           (playerRecords[j].wins == playerRecords[max].wins)) {
                               if (strcmp(playerRecords[j].username, playerRecords[max].username) < 0) {
                                   max = j;
                               }
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

/**
 *  Loads existing player records from a text file into a PlayerRecord array.
 *
 *  @param playerRecords[] Array for which to store existing records in
 *  @param numPlayerRecords Pointer to the number of elements in the array
 *  @return Void
 */

void loadPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords) {

    StrList playersTxtBuffer;
    FILE* playersRead = fopen(F_PLAYER_RECORDS, "r");

    if (playersRead == NULL) {
        printf("\n\nError: Could not read from players.txt\n\n");
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

/**
 *  Saves player records into a text file.
 *
 *  @param playerRecords[] Array from which to read records
 *  @param numPlayerRecords Pointer to the number of elements in the array
 *  @return Void
 */

void savePlayerRecords(PlayerRecord playerRecords[], int numPlayerRecords) {
    int i;
    FILE* playersWrite = fopen(F_PLAYER_RECORDS, "w");
    if (playersWrite == NULL) {
        printf("\n\nError! There was an error in saving the player records.\n\n");
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
