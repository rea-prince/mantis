/******************************************************************************
 *  Description     : Functions executed directly from the main menu
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#include "common.h"
#include "models.h"
#include "helpers.h"
#include "game.h"
#include "display.h"

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

    displayInReqPlayers(&game->numPlayers);

    /* SCAN FOR PLAYER INPUT */

    playerIdx = 0;
    do {

        // display current players

        if (playerIdx > 0) {
            displayPlayerUsernames(game, playerIdx);
        }

        // select player or add new player

        displayInPlayerRecords(playerRecords, numPlayerRecords, playerIdx, &option);

        // either initialize new player or use existing player

        if (option == 0) {
            do {
                duplicateFound = false;

                displayCustomHeader("Insert Username (36 characters maximum)");

                printf(  "\n+----+\n");
                printf(    "| >> | ");
                scanf(" %[^\n]", nameBuffer);
                while (scanf("%c", &flushBuffer) && flushBuffer != '\n');
                printf(    "+----+\n\n");

                // check for duplicates in current game

                for (name = 0; name < playerIdx; name++) {
                    if (strcmp(game->players[name].username, nameBuffer) == 0) {
                        printf("\n\nError: Name already listed; please try another name\n\n");
                        duplicateFound = true;
                    }
                }

                // check for duplicates in player records

                for (name = 0; name < *numPlayerRecords; name++) {
                    if (strcmp(playerRecords[name].username, nameBuffer) == 0) {
                        printf("\n\nError: Name already listed; please try another name\n\n");
                        duplicateFound = true;
                    }
                }

            } while (duplicateFound);

            // append user to records

            playerRecords[*numPlayerRecords + recordsDisplacement] = (PlayerRecord) {0};
            strcpy(playerRecords[*numPlayerRecords + recordsDisplacement].username, nameBuffer);

            // initialize player in current game

            game->players[playerIdx] = (Player) {0};
            strcpy(game->players[playerIdx].username, nameBuffer);

            ++recordsDisplacement;
            ++playerIdx;

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

    do {
        displayInMenuTopPlayers(&input);

        if (input != EXIT_TOP_PLAYERS) {
            iClear(0, 0, 60, 60);
            if (input == SORT_BY_WINS) {
                displayCustomHeader("DISPLAYING TOP PLAYERS BY WINS");
                sortPlayersByWins(playerRecords, numPlayers);
                displayTopPlayers(playerRecords, 10);
            } else if (input == SORT_BY_SCORE) {
                displayCustomHeader("DISPLAYING TOP PLAYERS BY HIGH SCORE");
                sortPlayersByScore(playerRecords, numPlayers);
                displayTopPlayers(playerRecords, 10);
            } else if (input == SHOW_ALL) {
                displayCustomHeader("DISPLAYING ALL PLAYER RECORDS");
                displayTopPlayers(playerRecords, numPlayers);
            }
        }
    } while (input != EXIT_TOP_PLAYERS);
}

void gameSettings(GameState *game) {
    iClear(0, 0, 60, 60);

    int input;

    do {
        displayInMenuGameSettings(&input);

        if (input == SET_WINNING_SCORE) {

            displayInSettingsWinningScore(&input);
            game->winningPoints = input;
            displayCustomHeader("Winning score successfully updated.");

        } else if (input == SET_SHUFFLE_SEED) {

            displayInSettingsShuffleSeed(&input);
            game->randSeed = input;
            displayCustomHeader("Shuffle seed successfully updated.");

        } else if (input == TOGGLE_DEBUG_MODE) {
            if (game->debugMode) {
                game->debugMode = false;
                displayCustomHeader("Debug mode has been turned off.");
            } else {
                game->debugMode = true;
                displayCustomHeader("Debug mode has been turned on.");
            }
        }
    } while (input != EXIT_GAME_SETTINGS);

}
