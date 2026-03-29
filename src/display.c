/******************************************************************************
 *  Description     : Functions for making the game more visually appealing
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "models.h"
#include "helpers.h"
#include "interface.h"

/* GENERIC PRINT */

void displayCustomHeader(char* header) {
    int i;
    int length = strlen(header);
    int padding = (CLI_LINE_LEN - 2 - length) / 2;

    iSetColor(I_COLOR_RED);
    printf("+");
    for (i = 0; i < CLI_LINE_LEN - 2; i++) {
        printf("-");
    }
    printf("+\n");

    printf("| %*s%s%*s |\n", padding - 1, "", header, CLI_LINE_LEN - 3 - length - padding, "");

    iSetColor(I_COLOR_PURPLE);
    printf("+");
    for (i = 0; i < CLI_LINE_LEN - 2; i++) {
        printf("-");
    }
    printf("+\n");

    iSetColor(I_COLOR_WHITE);
}

/* MENU DISPLAYS */

void displayMenuMain() {
    displayCustomHeader("Main Menu");
    printf("| Welcome to Mantis: CLI Edition! Please select an option. |\n");
    printf("|    [1] Start New Game                                    |\n");
    printf("|    [2] View Top Players                                  |\n");
    printf("|    [3] Change Game Settings                              |\n");
    printf("|    [0] Exit and Save                                     |\n");
    printf("+----------------------------------------------------------+\n");
}

void displayInMenuTopPlayers(int* input) {
    displayCustomHeader("View Top Players");
    printf("| Sort by:                                                 |\n");
    printf("|    [1] Most wins                                         |\n");
    printf("|    [2] Highest score                                     |\n");
    printf("|    [3] Show All players                                  |\n");
    printf("|    [0] Exit to main menu                                 |\n");
    printf("| WARNING: This will also change the order in the records. |\n");
    printf("+----------------------------------------------------------+\n");
    getInput(input, 0, N_SORT_Y, -1);
}

void displayInMenuGameSettings(int* input) {
    displayCustomHeader("Change Game Settings");
    printf("| Change settings for next match:                          |\n");
    printf("|    [1] Set winning points                                |\n");
    printf("|    [2] Set shuffle seed                                  |\n");
    printf("|    [3] Toggle debug mode (reveals cards when on)         |\n");
    printf("|    [0] Exit to main menu                                 |\n");
    printf("+----------------------------------------------------------+\n");
    getInput(input, 0, N_SET_Y, -1);
}

void displayTopPlayers(PlayerRecord playerRecords[], int numPlayers) {
    int i;

    printf(  "| HIGH SCORE | WINS | NAME                                 |\n");
    printf(  "+-----+----------------------------------------------------+\n");

    for (i = 0; i < numPlayers && i < MAX_LOGGED_PLAYERS; i++) {
        printf("| #%2d |   %2d | %3d  | %-36s |\n",
            i + 1,
            playerRecords[i].highScore,
            playerRecords[i].wins,
            playerRecords[i].username);
    }
    printf("+----------------------------------------------------------+\n");
}

/* PLAYER CREATION DISPLAYS */

void displayInReqPlayers(int* numPlayers) {
    displayCustomHeader("How many players?");
    getInput(numPlayers, MIN_PLAYERS, MAX_PLAYERS + 1, -1);
}

void displayInPlayerRecords(PlayerRecord playerRecords[], int* numPlayerRecords, int playerIdx, int* option) {
    int name;

    displayCustomHeader("SELECT PLAYER");
    printf("| For player %d:                                            |\n", playerIdx + 1);
    printf("|   0 | <Add new player>                                   |\n");
    for (name = 0; name < *numPlayerRecords && name < MAX_LOGGED_PLAYERS; name++) {
        printf("| %3d | %-50s |\n", name + 1, playerRecords[name].username);
    }
    printf("+----------------------------------------------------------+\n");

    getInput(option, 0, *numPlayerRecords + 1, -1);
}

void displayPlayerUsernames(GameState* game, int playerIdx) {
    int i;
    displayCustomHeader("CURRENT PLAYERS");
    for (i = 0; i < playerIdx; i++) {
        printf("| P%d: %-52s |\n", i + 1, game->players[i].username);
    }
    printf("+----------------------------------------------------------+\n");
}

/* GAMEPLAY DISPLAYS */

void displayBackCards(GameState* game) {

    int j, k;

    printf("+--------+-----+-----+-----+-----+-----+-----+-----+-------+\n");
    printf("| PLAYER |");

    iSetColor(I_COLOR_RED);
    printf(" RED ");
    iSetColor(0);
    printf("|");

    iSetColor(I_COLOR_WHITE);
    printf(" ORG ");
    iSetColor(0);
    printf("|");

    iSetColor(I_COLOR_YELLOW);
    printf(" YLW ");
    iSetColor(0);
    printf("|");

    iSetColor(I_COLOR_GREEN);
    printf(" GRN ");
    iSetColor(0);
    printf("|");

    iSetColor(I_COLOR_BLUE);
    printf(" BLU ");
    iSetColor(0);
    printf("|");

    iSetColor(I_COLOR_CYAN);
    printf(" IND ");
    iSetColor(0);
    printf("|");

    iSetColor(I_COLOR_PURPLE);
    printf(" VLT ");
    iSetColor(0);
    printf("| SCORE |\n");


    printf("+--------+-----+-----+-----+-----+-----+-----+-----+-------+\n");
    for (j = 0; j < game->numPlayers; j++) {
        printf("|   P%d   |", j + 1);
        for (k = 0; k < CARD_COLORS; k++) {
            if (k == 0) {
                iSetColor(I_COLOR_RED);
            } else if (k != 1){
                iSetColor(k);
            }

            printf("  %d  ", game->players[j].tankPile.cardsPerColor[k]);
            iSetColor(I_COLOR_WHITE);
            printf("|");
        }
        printf("  %2d   |\n", game->players[j].points);

        printf("+--------+-----+-----+-----+-----+-----+-----+-----+-------+\n");
    }
}

void displayInTurnInfo(GameState* game, int* playerAction) {
    printf("\n+----------+-----------------------------------------------+\n");
    printf(  "| TOP DECK | %c %c %c (%02d cards remaining)                    |\n",
            matchColorChar(game->drawPile.cards[0].back[0]),
            matchColorChar(game->drawPile.cards[0].back[1]),
            matchColorChar(game->drawPile.cards[0].back[2]),
            game->drawPile.totalCards
        );
    printf(  "+----------+--+--------------------------------------------+\n");
    printf(  "| PLAYER TURN | %-42s |\n",game->players[game->playerTurn].username);
    printf(  "+-------------+--------------------------------------------+\n");
    printf(  "| Player %d, what would you like to do?                     |\n", game->playerTurn + 1);
    printf(  "|    [1] Try to Score                                      |\n");
    printf(  "|    [2] Try to Steal                                      |\n");
    printf(  "+----------------------------------------------------------+\n");

    getInput(playerAction, 1, N_ACTION_Y, -1);

    printf("\n+----------------------------------------------------------+\n");
    printf(  "| Resolving turn for Player %d...                           |\n", game->playerTurn + 1);
    printf(  "+----------------------------------------------------------+\n");
}

void displayEndTurn(GameState* game) {
    printf("\n\n+==========================================================+\n");
    printf(    "| End of Player %d's turn!                                  |\n", game->playerTurn);
    printf(    "+==========================================================+\n\n\n");
}

void displayDrawnCard(Card drawnCard) {
    printf("\n+----------------------------------------------------------+\n");
    printf(  "| - Drawn card color reveal: %c (%d pt/s)!                   |\n", matchColorChar(drawnCard.color), drawnCard.value);
}

void displayScoreCard(GameState* game, int drawnColor, int totalPts, int playerIdx, int numPlayerCards) {
    if (numPlayerCards > 0) {
        printf("| - Player %d has (%d) %c card/s worth (%d) pts total!         |\n",
                game->playerTurn + 1,
                game->players[game->playerTurn].tankPile.cardsPerColor[drawnColor],
                matchColorChar(drawnColor), totalPts
            );
        printf("| - +%d points to Player %d's Score pile!                    |\n", totalPts, playerIdx + 1);
        printf("+----------------------------------------------------------+\n");
    } else {
        printf("| - Player %d has no %c cards...                             |\n", playerIdx + 1, matchColorChar(drawnColor));
        printf("| - Adding drawn card to Player %d's Tank                   |\n", playerIdx + 1);
        printf("+----------------------------------------------------------+\n");
    }

}

void displayInStealOptions(GameState* game, int* stealCardIdx) {
    int i;
    printf(  "| Who would you like to steal from?                        |\n");
    for (i = 0; i < game->numPlayers; i++) {
        if (i != game->playerTurn)
            printf(  "| [%d] Player %d                                             |\n", i + 1, i + 1);
    }
    printf( "+----------------------------------------------------------+\n");
    getInput(stealCardIdx, 1, game->numPlayers + 1, game->playerTurn + 1);
}

void displayStealCard(GameState* game, int drawnColor, int playerIdx, int totalPts, int stealIdx) {
    if (game->players[stealIdx].tankPile.cardsPerColor[drawnColor] > 0) {
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
    } else {
        printf("| - Player %d has no %c cards..                              |\n",
            stealIdx + 1,
            matchColorChar(drawnColor)
        );
        printf("| - Adding drawn card to Player %d's Tank                   |\n", stealIdx + 1);
        printf("+----------------------------------------------------------+\n");
    }
}

/* DEBUG MODE DISPLAYS */

void displayCards(DrawPile* drawPile) {

    int i;

    displayCustomHeader("DISPLAYING ALL CARDS");
    printf(  "| CARD | FRONT | BACK  | VALUE                             |\n");
    printf(  "+------+-------+-------+-----------------------------------+\n");

    for (i = 0; i < drawPile->totalCards; i++) {
        printf("| %4d |   %c   | %c %c %c | %-33d |\n",
            i + 1,
            matchColorChar(drawPile->cards[i].color),
            matchColorChar(drawPile->cards[i].back[0]),
            matchColorChar(drawPile->cards[i].back[1]),
            matchColorChar(drawPile->cards[i].back[2]),
            drawPile->cards[i].value
        );
    }
    printf(  "+------+-------+-------+-----------------------------------+\n");
}

void displayPlayerCards(DrawPile* drawPile, Player players[], int numPlayers) {

    int j, k, z;

    displayCustomHeader("DISPLAYING PLAYER CARDS");
    printf(  "| PLAYER | DECK | FRONT | BACK  | VALUE                    |\n");
    printf(  "+--------+------+-------+----------------------------------+\n");

    // loop through each player

    for (j = 0; j < numPlayers; j++) {

        // loop through each color deck

        for (k = 0; k <= CARD_COLORS; k++) {

            // loop through each card in that color deck

            for (z = 0; z < players[j].tankPile.cardsPerColor[k]; z++) {
                printf("| %4d   | %3d  |   %c   | %c %c %c | %-24d |\n",
                    j + 1,
                    k + 1,
                    matchColorChar(players[j].tankPile.cards[k][z].color),
                    matchColorChar(players[j].tankPile.cards[k][z].back[0]),
                    matchColorChar(players[j].tankPile.cards[k][z].back[1]),
                    matchColorChar(players[j].tankPile.cards[k][z].back[2]),
                    players[j].tankPile.cards[k][z].value
                );
            }
        }
        printf(  "+--------+------+-------+----------------------------------+\n");
    }
}

/* SETTINGS DISPLAYS */

void displayInSettingsWinningScore(int* input) {
    displayCustomHeader("Set winning points (140 maximum)");

    getInput(input, 1, MAX_WIN_SCORE + 1, -1);
}

void displayInSettingsShuffleSeed(int* input) {
    displayCustomHeader("Set shuffle seed (integer >= 0; i.e. 67)");

    getInput(input, 0, -1, -1);
}
