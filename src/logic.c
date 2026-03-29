/******************************************************************************
 *  Description     : Functions necessary for modifying the game state and
 *                    performing game logic. Functions are arranged starting
 *                    from the smallest possible interactions
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#include "common.h"
#include "models.h"
#include "helpers.h"
#include "display.h"

/**
 *  Puts the drawn card into the score pile of the player whose turn it is.
 *
 *  @param game Pointer to the current game state struct
 *  @param drawnCard The card drawn by the player from the drawPile
 *  @return Returns the total points of the current player
 */

int scoreCard(GameState* game, Card drawnCard) {

    enum Color drawnColor = drawnCard.color;

    // check for cards

    int playerIdx = game->playerTurn;
    int numPlayerCards = game->players[playerIdx].tankPile.cardsPerColor[drawnColor];

    if (numPlayerCards > 0) {
        int numScoreCards = game->players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX];

        int i;
        int totalPts = 0;

        for (i = numPlayerCards - 1; i >= 0 ; i--) {
            totalPts += game->players[playerIdx].tankPile.cards[drawnColor][i].value;
            game->players[playerIdx].tankPile.cards[SCORE_PILE_IDX][numScoreCards] = game->players[playerIdx].tankPile.cards[drawnColor][i];
            game->players[playerIdx].tankPile.cards[drawnColor][i] = (Card) {0};

            --game->players[playerIdx].tankPile.totalCards;
            ++numScoreCards;
            --numPlayerCards;
        }
        printf("| - Player %d has (%d) %c card/s worth (%d) pts total!         |\n",
                game->playerTurn + 1,
                game->players[game->playerTurn].tankPile.cardsPerColor[drawnColor],
                matchColorChar(drawnColor), totalPts
            );
        printf("| - +%d points to Player %d's Score pile!                    |\n", totalPts, playerIdx + 1);
        printf("+----------------------------------------------------------+\n");

        game->players[playerIdx].tankPile.cardsPerColor[drawnColor] = numPlayerCards;
        game->players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX] = numScoreCards;
    } else {
        game->players[playerIdx].tankPile.cards[drawnColor][0] = drawnCard;
        ++game->players[playerIdx].tankPile.cardsPerColor[drawnColor];

        printf("| - Player %d has no %c cards...                             |\n", playerIdx + 1, matchColorChar(drawnColor));
        printf("| - Adding drawn card to Player %d's Tank                   |\n", playerIdx + 1);
        printf("+----------------------------------------------------------+\n");
    }

    // update score
    game->players[playerIdx].points = computePlayerScore(game->players[playerIdx].tankPile);
    return game->players[playerIdx].points;
}

/**
 *  Steals a card from the player at stealIdx to be put into the deck of
 *  playerIdx based on the drawn card.
 *
 *  Case 1 : players[stealIdx] does not have a card with the same color as the one drawn
 *     - The card is put into that player's deck
 *     - The player who stole gets nothing
 *  Case 2 : players[stealIdx] has a card of the same color as the one drawn
 *     - All their cards of that color are taken
 *     - Cards taken from that player are placed into the stealer's deck
 *
 *  @param game Pointer to the game state struct
 *  @param stealIdx The index of the player who's being stolen from
 *  @param drawnCard The card drawn by the player from the drawPile
 *  @return void
 */

void stealCard(GameState* game, int stealIdx, Card drawnCard) {

    int numPlayerCards, numStealCards;
    int playerIdx = game->playerTurn;

    enum Color drawnColor = drawnCard.color;
    if (game->players[stealIdx].tankPile.cardsPerColor[drawnColor] > 0) {

        int i;
        int totalPts = 0;

        numPlayerCards = game->players[playerIdx].tankPile.cardsPerColor[drawnColor];
        numStealCards = game->players[stealIdx].tankPile.cardsPerColor[drawnColor];

        for (i = 0; i < game->players[stealIdx].tankPile.cardsPerColor[drawnColor]; i++) {
            totalPts += game->players[stealIdx].tankPile.cards[drawnColor][numStealCards - 1].value;
            game->players[playerIdx].tankPile.cards[drawnColor][numPlayerCards] = game->players[stealIdx].tankPile.cards[drawnColor][numStealCards - 1];
            ++numPlayerCards;
            --numStealCards;
        }
        printf("| - Player %d has (%d) %c card/s worth (%d) pts total!         |\n",
            stealIdx + 1,
            game->players[stealIdx].tankPile.cardsPerColor[drawnColor],
            matchColorChar(drawnColor),
            totalPts
        );
        printf("| - +%d (%c) cards to Player %d's Tank!                       |\n",
            game->players[stealIdx].tankPile.cardsPerColor[drawnColor],
            matchColorChar(drawnColor),
            playerIdx + 1
        );
        printf("+----------------------------------------------------------+\n");

        game->players[playerIdx].tankPile.cardsPerColor[drawnColor] = numPlayerCards;
        game->players[stealIdx].tankPile.cardsPerColor[drawnColor] = numStealCards;

    } else {
        printf("| - Player %d has no %c cards..                              |\n",
            stealIdx + 1,
            matchColorChar(drawnColor)
        );
        printf("| - Adding drawn card to Player %d's Tank                   |\n", stealIdx + 1);
        printf("+----------------------------------------------------------+\n");

        game->players[stealIdx].tankPile.cards[drawnColor][0] = drawnCard;
        ++game->players[stealIdx].tankPile.cardsPerColor[drawnColor];
    }

}

/**
 *  Simulates a player's turn in the game, then increments the player turn tracker
 *  inside the game state struct.
 *
 *  Case 1 : Player chooses to score
 *     - scoreCard() is called
 *     - All cards fo the same color as drawnCard is placed in
 *       the player's score pile
 *  Case 2 : Player chooses to steal
 *     - Player is prompted for further input on who to steal from
 *     - stealCard() is called on the player to be stolen from
 *
 *  @param game Pointer to the game state struct
 *  @return Void
 */

void takeTurn(GameState* game) {

    int playerAction;

    if (game->drawPile.totalCards > 0) {

        displayTurnInfo(game, &playerAction);

        Card drawnCard = drawCard(&game->drawPile);
        int i;

        if (playerAction == SCORE) {
            // if player chooses to score
            printf("\n+----------------------------------------------------------+\n");
            printf(  "| - Drawn card color reveal: %c (%d pt/s)!                   |\n", matchColorChar(drawnCard.color), drawnCard.value);
            if (scoreCard(game, drawnCard) >= game->winningPoints) {
                game->winner = game->playerTurn;
                game->gameWon = true;
            }

        } else if (playerAction == STEAL) {
            /* PLACE HOLDER OUTPUTS */

            // if player chooses to steal
            printf(  "| Who would you like to steal from?                        |\n");
            for (i = 0; i < game->numPlayers; i++) {
                if (i != game->playerTurn)
                    printf(  "| [%d] Player %d                                             |\n", i + 1, i + 1);
            }
            printf( "+----------------------------------------------------------+\n");

            /* PLACE HOLDER INPUTS */
            int stealCardIdx;

            getInput(&stealCardIdx, 1, game->numPlayers + 1, game->playerTurn + 1);

            /* END OF PLACEHOLDER */

            printf("\n+----------------------------------------------------------+\n");
            printf(  "| - Drawn card color reveal: %c (%d pt/s)!                   |\n", matchColorChar(drawnCard.color), drawnCard.value);
            stealCard(game, stealCardIdx - 1, drawnCard);
        }

        game->playerTurn = (game->playerTurn + 1) % game->numPlayers;

    } else {

        /* DRAW */

        game->gameWon = true;
    }

    displayEndTurn(game);
}

/**
 *  Populates the drawPile inside the game struct, and continuously plays
 *  a rotation of turns among players in the game, displaying all
 *  players' card information for each turn taken until a player wins.
 *  Calls takeTurn() on the player whose turn it is.
 *
 *  @param game Pointer to the game state struct
 *  @return Void
 */

void playGame(GameState* game) {

    int i;

    /* DISPLAY CARDS */

    if (game->debugMode) {
        displayCards(&game->drawPile);
    }

    /* POPULATE DECK */

    for (i = 0; i < game->numPlayers; i++) {
        populateDeck(&game->drawPile, &game->players[i].tankPile);
    }

    /* PLAY ROUNDS */

    do {

        /* DISPLAY CARDS */

        if (game->debugMode) {
            displayPlayerCards(&game->drawPile, game->players, game->numPlayers);
        }

        displayBackCards(game);

        takeTurn(game);

    } while (game->gameWon == false);
}

/**
 *  Starts a new game by clearing the terminal, prompting the user for the
 *  number of players, either adding a new player or choosing from the selction,
 *  and calling playGame() to start
 *  @return Void
 */

void newGame(GameState* game, PlayerRecord playerRecords[], int *numPlayerRecords) {
    iClear(0, 0, 60, 60);

    int playerIdx, i, j;
    int recordsDisplacement = 0; // keeping track of players added; for preventing duplicates

    StrName nameBuffer;
    char flushBuffer;

    bool duplicateFound;
    int name;
    int option;

    /* REQUEST NUMBER OF PLAYERS */

    displayCustomBox("How many players?");

    getInput(&game->numPlayers, MIN_PLAYERS, MAX_PLAYERS + 1, -1);

    /* SCAN FOR PLAYER INPUT */

    playerIdx = 0;
    do {
        duplicateFound = false;

        // display current players

        if (playerIdx > 0) {
            displayPlayerUsernames(game, playerIdx);
        }

        displayPlayerRecords(playerRecords, numPlayerRecords, playerIdx);

        // select player or add new player

        getInput(&option, 0, *numPlayerRecords + 1, -1);

        // either initialize new player or use existing player

        if (option == 0) {
            printf("+----------------------------------------------------------+\n");
            printf("| Insert P%d username (36 chars max):                       |\n", (playerIdx + 1));
            printf("+----------------------------------------------------------+\n");

            printf(  "\n+----+\n");
            printf(    "| >> | ");
            scanf(" %[^\n]", nameBuffer);
            while (scanf("%c", &flushBuffer) && flushBuffer != '\n');
            printf(    "+----+\n\n");

            // check for duplicates in current game

            for (name = 0; name < playerIdx; name++) {
                if (strcmp(game->players[name].username, nameBuffer) == 0) {
                    printf("\nError: Name already listed; please try another name\n");
                    duplicateFound = 1;
                }
            }
            if (!duplicateFound) {

                // append user to records

                playerRecords[*numPlayerRecords + recordsDisplacement] = (PlayerRecord) {0};
                strcpy(playerRecords[*numPlayerRecords + recordsDisplacement].username, nameBuffer);

                // initialize player in current game

                game->players[playerIdx] = (Player) {0};
                strcpy(game->players[playerIdx].username, nameBuffer);

                ++recordsDisplacement;
                ++playerIdx;
            }

        } else if (option > 0 && option <= *numPlayerRecords) {

            // initialize player in current game

            game->players[playerIdx] = (Player) {0};
            strcpy(game->players[playerIdx].username, playerRecords[option - 1].username);

            playerIdx++;
        }

    } while (playerIdx < game->numPlayers);

    /* DISPLAY ALL PLAYERS */

    displayPlayerUsernames(game, playerIdx);

    *numPlayerRecords += recordsDisplacement;

    /* LOAD DECK */

    FILE* mantisDeck = fopen(F_MANTIS_DECK, "r");
    if (mantisDeck == NULL) {
        printf("\nError: Could not load cards\n");
    } else {
        createDeck(mantisDeck, game);
        fclose(mantisDeck);

        /* PLAY GAME */

        playGame(game);

        /* SEARCH FOR WINNER */

        int winners;

        sortPlayersByPoints(game->players, game->numPlayers);

        if (game->players[0].points > game->players[1].points) {

            // Case 1: player 1 has more points than player 2

            game->winner = 0;
            printf("WINNER: %s (P%d) with %d points!\n\n", game->players[game->winner].username, 1, game->players[game->winner].points);
        } else if (game->players[0].points == game->players[1].points) {

            // Case 2: player 1 and 2 have equal points

            if (game->players[0].tankPile.totalCards > game->players[1].tankPile.totalCards) {

                // Case 2a: player 1 has more tank cards than player 2

                game->winner = 0;
                printf("WINNER: %s (P%d) with %d points!\n\n", game->players[game->winner].username, 1, game->players[game->winner].points);

            } else {

                // Case 2b: player 1, 2, and possibly others have equal points and tank cards

                winners = 0;
                int a;

                // count number of winners with such case

                for (a = 0; a < game->numPlayers; a++) {
                    if (game->players[0].points == game->players[a].points &&
                        game->players[0].tankPile.totalCards == game->players[a].tankPile.totalCards) {
                            printf("WINNER/s: %s (P%d) with %d points!\n\n", game->players[a].username, a + 1, game->players[a].points);
                            ++winners;
                        }
                }
            }
        }

        // update player (sorted already)

        for (i = 0; i < game->numPlayers; i++) {
            bool playerFound = false;

            // match player to records

            for (j = 0; j < *numPlayerRecords && !playerFound; j++) {
               if (strcmp(playerRecords[j].username, game->players[i].username) == 0) {

                   // update high score

                   if (game->players[i].points > playerRecords[j].highScore) {
                       playerRecords[j].highScore = game->players[i].points;
                   }

                   // count win; (i < winners) in case there's multiple

                   if (i < winners) {
                       ++playerRecords[j].wins;
                   }
                   playerFound = true;
               }
            }
        }

        /* SORT PLAYER RECORDS */
        // sorted by wins by default
        sortPlayersByWins(playerRecords, *numPlayerRecords);
    }
}

/**
 *  Lists the top players from players.txt according to either most amount
 *  of wins or highest score achieved.
 *
 *  @return Void
 */

void topPlayers(PlayerRecord playerRecords[], int numPlayers) {
    iClear(0, 0, 60, 60);

    int input;

    displayMenuTopPlayers();

    getInput(&input, 0, N_SORT_Y, -1);

    if (input != EXIT_TOP_PLAYERS) {
        if (input == SORT_BY_WINS) {
            sortPlayersByWins(playerRecords, numPlayers);
        } else if (input == SORT_BY_SCORE) {
            sortPlayersByScore(playerRecords, numPlayers);
        }
        displayTopPlayers(playerRecords, numPlayers);
    }
}

void gameSettings(GameState *game) {
    iClear(0, 0, 60, 60);

    displayMenuGameSettings();

    int input;

    getInput(&input, 0, N_SET_Y, -1);

    if (input == SET_WINNING_SCORE) {
        displayCustomBox("Set winning points (140 maximum)");

        getInput(&input, 1, MAX_WIN_SCORE + 1, -1);

        game->winningPoints = input;

    } else if (input == SET_SHUFFLE_SEED) {
        displayCustomBox("Set shuffle seed (integer >= 0; i.e. 67)");

        getInput(&input, 0, -1, -1);

        game->randSeed = input;
    } else if (input == TOGGLE_DEBUG_MODE) {
        if (game->debugMode) {
            game->debugMode = false;
            displayCustomBox("Debug mode has been turned off.");
        } else {
            game->debugMode = true;
            displayCustomBox("Debug mode has been turned on.");
        }
    }

}
