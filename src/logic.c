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
#include "helpers.h"

/* TO-DO */



/* -------------------- */
/* SMALLEST POSSIBLE ACTIONS */


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

    int i;
    int numPlayerCards, numStealCards;
    int playerIdx = game->playerTurn;

    enum Color drawColor = drawnCard.color;
    if (game->players[stealIdx].tankPile.cardsPerColor[drawColor] > 0) {
        numPlayerCards = game->players[playerIdx].tankPile.cardsPerColor[drawColor];
        numStealCards = game->players[stealIdx].tankPile.cardsPerColor[drawColor];

        for (i = 0; i < game->players[stealIdx].tankPile.cardsPerColor[drawColor]; i++) {
            game->players[playerIdx].tankPile.cards[drawColor][numPlayerCards] = game->players[stealIdx].tankPile.cards[drawColor][numStealCards - 1];
            ++numPlayerCards;
            --numStealCards;
        }

        game->players[playerIdx].tankPile.cardsPerColor[drawColor] = numPlayerCards;
        game->players[stealIdx].tankPile.cardsPerColor[drawColor] = numStealCards;

    } else {
        game->players[stealIdx].tankPile.cards[drawColor][0] = drawnCard;
        ++game->players[stealIdx].tankPile.cardsPerColor[drawColor];
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

        for (i = numPlayerCards - 1; i >= 0 ; i--) {
            game->players[playerIdx].tankPile.cards[SCORE_PILE_IDX][numScoreCards] = game->players[playerIdx].tankPile.cards[drawnColor][i];
            game->players[playerIdx].tankPile.cards[drawnColor][i] = (Card) {0};
            ++numScoreCards;
            --numPlayerCards;
        }

        game->players[playerIdx].tankPile.cardsPerColor[drawnColor] = numPlayerCards;
        game->players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX] = numScoreCards;
    } else {
        game->players[playerIdx].tankPile.cards[drawnColor][0] = drawnCard;
        ++game->players[playerIdx].tankPile.cardsPerColor[drawnColor];
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

bool takeTurn(GameState* game, enum Action playerAction) {

    Card drawnCard = drawCard(&game->drawPile);
    int i;
    int score;
    bool gameWon = false;

    if (playerAction == SCORE) {
        // if player chooses to score
        score = scoreCard(game, drawnCard);
        if (score >= WIN_SCORE) {
            game->winner = game->players[game->playerTurn];
            gameWon = true;
        }

    } else if (playerAction == STEAL) {
        /* PLACE HOLDER OUTPUTS */

        // if player chooses to steal
        printf("Who would you like to steal from?\n");
        for (i = 0; i < game->numPlayers; i++) {
            printf("[%d] Player %d\n", i + 1, i + 1);
        }

        /* PLACE HOLDER INPUTS */
        int stealCardIdx;

        scanf("%d", &stealCardIdx);
        /* END OF PLACEHOLDER */

        stealCard(game, stealCardIdx, drawnCard);
    }

    game->playerTurn = (game->playerTurn + 1) % game->numPlayers;

    return gameWon;
}

/* -------------- */
/* SIMULATE ROUND */

// Loop through players
// Call playerTurn()

int playRound(GameState* game) {
    int i;
    bool gameWon = false;
    int input;

    /* TEMPORARY OUTPUT */

    // print players' cards
    for (i = 0; i < game->numPlayers; i++) {
        printf("P%d CARDS : R:%d | O:%d | Y:%d | G:%d | B:%d | I:%d | V:%d\n", i + 1,
                game->players[i].tankPile.cardsPerColor[0],
                game->players[i].tankPile.cardsPerColor[1],
                game->players[i].tankPile.cardsPerColor[2],
                game->players[i].tankPile.cardsPerColor[3],
                game->players[i].tankPile.cardsPerColor[4],
                game->players[i].tankPile.cardsPerColor[5],
                game->players[i].tankPile.cardsPerColor[6]
            );
    }

    printf("TOP DECK : %c%c%c (%d cards remaining)\n",
            matchColorChar(game->drawPile.cards[0].back[0]),
            matchColorChar(game->drawPile.cards[0].back[1]),
            matchColorChar(game->drawPile.cards[0].back[2]),
            game->drawPile.totalCards
        );


    for (i = 0; i < game->numPlayers && !gameWon; i++) {
        /* TEMPORARY INPUT */

        printf("Player %d, what would you like to do?\n", i + 1);
        printf("\t[1] Try to Score\n");
        printf("\t[2] Try to Steal\t\t");

        printf(">>");
        scanf("%d", &input);
        --input; // offset since enums start at 1
        takeTurn(game, input);
    }


    return 1;
}




/* ------------- */
/* SIMULATE GAME */

int playGame(GameState* game) {

    // state vars for game condition
        // win bool
        // winner placeholder struct

    // initialize deck (randomized)




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

int initGame() {
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

    /* LOAD DECK */

    FILE* mantisDeck = fopen("mantis.txt", "r");
    if (mantisDeck == NULL) {
        printf("Error: Could not load cards\n");
    } else {
        createDeck(mantisDeck, &game.drawPile);
        fclose(mantisDeck);
    }

    /* PLAY GAME */

    // playGame(&drawPile, players);
    debugGame(&game.drawPile, game.players, game.numPlayers);

    // Display winner/loser

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
