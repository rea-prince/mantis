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

/* GENERIC PRINT */

void displayCustomBox(char* strInput) {
    int length = strlen(strInput);
    int i;

    printf("\n+");
    for (i = 0; i < length + 2; i++) {
        printf("-");
    }
    printf("+\n");

    printf("| %s |\n", strInput);

    printf("+");
    for (i = 0; i < length + 2; i++) {
        printf("-");
    }
    printf("+\n");
}

/* MENU DISPLAYS */

void displayMenuMain() {
    printf("+----------------------------------------------------------+\n");
    printf("| Main Menu                                                |\n");
    printf("+----------------------------------------------------------+\n");
    printf("| Welcome to Mantis: CLI Edition! Please select an option. |\n");
    printf("|    [1] New Game                                          |\n");
    printf("|    [2] Top Players                                       |\n");
    printf("|    [3] Game Settings                                     |\n");
    printf("|    [0] Exit and Save                                     |\n");
    printf("+----------------------------------------------------------+\n");
}

void displayMenuTopPlayers() {
    printf("+----------------------------------------------------------+\n");
    printf("| Sort by:                                                 |\n");
    printf("|    [1] Most wins                                         |\n");
    printf("|    [2] Highest score                                     |\n");
    printf("|    [0] Exit to main menu                                 |\n");
    printf("| WARNING: This will also change the order in the records. |\n");
    printf("+----------------------------------------------------------+\n");
}

void displayMenuGameSettings() {
    printf("+----------------------------------------------------------+\n");
    printf("| Change settings for next match:                          |\n");
    printf("|    [1] Set winning points                                |\n");
    printf("|    [2] Set shuffle seed                                  |\n");
    printf("|    [3] Toggle debug mode (reveals cards when on)         |\n");
    printf("|    [0] Exit to main menu                                 |\n");
    printf("+----------------------------------------------------------+\n");
}

void displayTopPlayers(PlayerRecord playerRecords[], int numPlayers) {
    int i;

    printf("\n+----------------------------------------------------------+\n");
    printf(  "| HIGH SCORE | WINS | NAME                                 |\n");
    printf(  "+-----+----------------------------------------------------+\n");

    for (i = 0; i < 10; i++) {
        printf("| #%2d |   %2d | %3d  | %-36s |\n",
            i + 1,
            playerRecords[i].highScore,
            playerRecords[i].wins,
            playerRecords[i].username);
    }
    printf("+----------------------------------------------------------+\n");
}

/* PLAYER CREATION DISPLAYS */

void displayPlayerRecords(PlayerRecord playerRecords[], int *numPlayerRecords, int playerIdx) {
    int name;

    printf("+----------------------------------------------------------+\n");
    printf("| Select Player %d:                                         |\n", playerIdx + 1);
    printf("|   0 | <Add new player>                                   |\n");
    for (name = 0; name < *numPlayerRecords; name++) {
        printf("| %3d | %-50s |\n", name + 1, playerRecords[name].username);
    }
    printf("+----------------------------------------------------------+\n");
}

void displayPlayerUsernames(GameState* game, int playerIdx) {
    int i;
    printf("+----------------------------------------------------------+\n");
    for (i = 0; i < playerIdx; i++) {
        printf("| P%d: %-52s |\n", i + 1, game->players[i].username);
    }
    printf("+----------------------------------------------------------+\n");
}

/* GAMEPLAY DISPLAYS */

void displayBackCards(GameState* game) {

    int j;

    printf("+--------+-----+-----+-----+-----+-----+-----+-----+-------+\n");
    printf("| PLAYER | RED | ORG | YLW | GRN | BLU | IND | VLT | SCORE |\n");
    printf("+--------+-----+-----+-----+-----+-----+-----+-----+-------+\n");
    for (j = 0; j < game->numPlayers; j++) {
        printf("|   P%d   |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %2d   |\n", j + 1,
                game->players[j].tankPile.cardsPerColor[0],
                game->players[j].tankPile.cardsPerColor[1],
                game->players[j].tankPile.cardsPerColor[2],
                game->players[j].tankPile.cardsPerColor[3],
                game->players[j].tankPile.cardsPerColor[4],
                game->players[j].tankPile.cardsPerColor[5],
                game->players[j].tankPile.cardsPerColor[6],
                game->players[j].points
            );
            printf("+--------+-----+-----+-----+-----+-----+-----+-----+-------+\n");
    }
}

void displayTurnInfo(GameState* game, int* playerAction) {
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

/* DEBUG MODE DISPLAYS */

void displayCards(DrawPile* drawPile) {

    int i;

    printf("\n+----------------------------------------------------------+\n");
    printf(  "|                   DISPLAYING ALL CARDS                   |\n");
    printf(  "+------+-------+-------+-----------------------------------+\n");
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

    printf("\n+----------------------------------------------------------+\n");
    printf(  "|                 DISPLAYING PLAYER CARDS                  |\n");
    printf(  "+--------+------+-------+----------------------------------+\n");
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
