/******************************************************************************
 *  Description     : Functions for making the game more visually appealing
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 ******************************************************************************/

#include <stdio.h>
#include "common.h"
#include "models.h"
#include "helpers.h"

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
