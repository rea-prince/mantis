/******************************************************************************
 *  Description     : Functions necessary for modifying the game state and
 *                    performing game logic. Functions are arranged starting
 *                    from the smallest possible interactions
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef LOGIC_C // Include this to prevent redefinition error
#define LOGIC_C // Include this to prevent redefinition error

#include "common.h"
#include "models.h"
#include "helpers.h"


/* This function steals a card from the player at stealIdx to be put into
 * the deck of playerIdx based on the drawn card
 * Case 1 : players[stealIdx] does not have a card with the same color as the one drawn
 *    - The card is put into that player's deck
 *    - The player who stole gets nothing
 * Case 2 : players[stealIdx] has a card of the same color as the one drawn
 *    - All their cards of that color are taken
 *    - Cards taken from that player are placed into the stealer's deck
 *
 * @param players[] The array of players in the game
 * @param playerIdx The index of the player whose turn it is
 * @param stealIdx The index of the player who's being stolen from
 * @param drawnCard The card drawn from the deck for comparison
 * @return void
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

// Score

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


/* -------------------- */
/* SIMULATE PLAYER TURN */
// take players array, deck array, turn index, player action
// If steal,
// If score,

void takeTurn(GameState* game, enum Action playerAction) {

    Card drawnCard = drawCard(&game->drawPile);
    int i;

    if (playerAction == SCORE) {
        // if player chooses to score
        printf("\n+----------------------------------------------------------+\n");
        printf(  "| - Drawn card color reveal: %c (%d pt/s)!                   |\n", matchColorChar(drawnCard.color), drawnCard.value);
        if (scoreCard(game, drawnCard) >= WIN_SCORE) {
            game->winner = game->players[game->playerTurn];
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
        printf(  "\n+----+\n");
        printf(    "| >> | ");
        scanf("%d", &stealCardIdx);
        printf(    "+----+\n");
        /* END OF PLACEHOLDER */

        printf("\n+----------------------------------------------------------+\n");
        printf(  "| - Drawn card color reveal: %c (%d pt/s)!                   |\n", matchColorChar(drawnCard.color), drawnCard.value);
        stealCard(game, stealCardIdx - 1, drawnCard);


    }

    printf("\n\n+==========================================================+\n");
    // printf(    "| End of Player %d's turn! Press enter to continue. |\n", game->playerTurn + 1);
    printf(    "| End of Player %d's turn!                                  |\n", game->playerTurn + 1);
    printf(    "+==========================================================+\n\n\n");


    game->playerTurn = (game->playerTurn + 1) % game->numPlayers;

    // scanf("%*c %*c");
}

/* -------------- */
/* SIMULATE ROUND */

// Loop through players
// Call playerTurn()

void playRound(GameState* game) {
    int i, j;
    int input;

    /* TEMPORARY OUTPUT */


    for (i = 0; i < game->numPlayers && !game->gameWon; i++) {
        /* TEMPORARY INPUT */
        // print players' cards
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

        printf("\n+----------+-----------------------------------------------+\n");
        printf(  "| TOP DECK | %c %c %c (%02d cards remaining)                    |\n",
                matchColorChar(game->drawPile.cards[0].back[0]),
                matchColorChar(game->drawPile.cards[0].back[1]),
                matchColorChar(game->drawPile.cards[0].back[2]),
                game->drawPile.totalCards
            );
        printf(  "+----------+-----------------------------------------------+\n");

        printf(  "| Player %d, what would you like to do?                     |\n", i + 1);
        printf(  "|\t[1] Try to Score                                   |\n");
        printf(  "|\t[2] Try to Steal                                   |\n");
        printf(  "+----------------------------------------------------------+\n");

        printf(  "\n+----+\n");
        printf(    "| >> | ");
        scanf("%d", &input);
        printf(    "+----+\n");

        --input; // offset since enums start at 1

        printf("\n+----------------------------------------------------------+\n");
        printf(  "| Resolving turn for Player %d...                           |\n", i + 1);
        printf(  "+----------------------------------------------------------+\n");

        takeTurn(game, input);
    }
}




/* ------------- */
/* SIMULATE GAME */

int playGame(GameState* game) {

    /* POPULATE DECK */

    for (int a = 0; a < game->numPlayers; a++) {
        populateDeck(&game->drawPile, &game->players[a].tankPile);
    }

    /* PLAY ROUNDS */

    do {
        playRound(game);
    } while (game->gameWon == false);

    // ROUND simulation loops while condition is not met
    return 1;
}

int debugGame(DrawPile* drawPile, Player players[], int playerCount) {


    /* Display cards */

    printf("DISPLAYING CARDS\n\n");
    for (int i = 0; i < drawPile->totalCards; i++) {

        printf("\nCard %d : \n", i + 1);
        printf("\t color: %c\n", matchColorChar(drawPile->cards[i].color));
        printf("\t back : %c %c %c\n",
            matchColorChar(drawPile->cards[i].back[0]),
            matchColorChar(drawPile->cards[i].back[1]),
            matchColorChar(drawPile->cards[i].back[2])
        );
        printf("\t value: %d\n", drawPile->cards[i].value);
    }

    /* INITIALIZE PLAYER */

    for (int a = 0; a < playerCount; a++) {
        populateDeck(drawPile, &players[a].tankPile);
    }

    /* Display player info */

    printf("DISPLAYING PLAYER CARDS\n\n");
    for (int j = 0; j < playerCount; j++) {

        printf("\nPlayer %d : \n", j + 1);

        // player cards
        // loop through each color

        for (int k = 0; k < 7; k++) {

            // loop for each color deck

            for (int z = 0; z < players[j].tankPile.cardsPerColor[k]; z++) {
                printf("\n\tCard %c %d: \n", matchColorChar(k), z);
                printf("\t\t color: %c\n", matchColorChar(players[j].tankPile.cards[k][z].color));
                printf("\t\t back : %c %c %c\n",
                    matchColorChar(players[j].tankPile.cards[k][z].back[0]),
                    matchColorChar(players[j].tankPile.cards[k][z].back[1]),
                    matchColorChar(players[j].tankPile.cards[k][z].back[2])
                );
                printf("\t\t value: %d\n", players[j].tankPile.cards[k][z].value);
            }
        }

    }

    return 1;
}

/* --------------- */
/* INITIALIZE GAME */

void clearTerminal(void)
{
    for (int i = 0; i < 50; i++)
            printf("\n");
    printf("\033[H");
}

int initGame() {
    // iClear(0, 0, 32, 32);
    clearTerminal();

    GameState game = {0};
    int playerIdx;

    /* INITIALIZE PLAYERS */

    printf("How many players? : ");
    scanf("%d", &game.numPlayers);

    StrName nameBuffer;

    playerIdx = 0;
    do {
        printf("P%d : ", (playerIdx + 1));
        scanf("%s", nameBuffer);
        bool duplicateFound = false;
        int name;

        /*** TEMPORARY ***/
        // check for duplicates
        for (name = 0; name < playerIdx; name++) {
            if (strcmp(game.players[name].username, nameBuffer) == 0) {
                printf("Error: Name already listed; please try another name\n");
                duplicateFound = 1;
            }
        }
        if (!duplicateFound) {
            strcpy(game.players[playerIdx].username, nameBuffer);
            game.players[playerIdx].points = 0;
            playerIdx++;
        }
    } while (playerIdx < game.numPlayers);
    printf("\n================\n\n");

    /* LOAD DECK */

    FILE* mantisDeck = fopen("mantis.txt", "r");
    if (mantisDeck == NULL) {
        printf("Error: Could not load cards\n");
    } else {
        createDeck(mantisDeck, &game.drawPile);
        fclose(mantisDeck);
    }

    /* PLAY GAME */

    playGame(&game);

    // debugGame(&game.drawPile, game.players, game.numPlayers);

    printf("WINNER: %s with %d points!\n", game.winner.username, game.winner.points);


    /* LOG PLAYER STATS */

    // open players.txt

    FILE* playersRead = fopen("players.txt", "r");
    if (playersRead == NULL) {
        printf("Error: Could not read from players.txt\n");
    }
    FILE* playersWrite = fopen("players.txt", "w");
    if (playersWrite == NULL) {
        printf("Error: Could not write to players.txt\n");
    }

    // append names if non existent

    // edit scores

    // re-sort players.txt by high score

    // close players.txt
    fclose(playersRead);
    fclose(playersWrite);

    return 1; // return for success
}


#endif // LOGIC_C; Include this to prevent redefinition error
