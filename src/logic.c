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
 * @return 1 if the function is successful
 */
int stealCard(Player players[], int playerIdx, int stealIdx, Card drawnCard) {

    int i;
    int numPlayerCards, numStealCards;

    enum Color drawColor = drawnCard.color;
    if (players[stealIdx].tankPile.cardsPerColor[drawColor] > 0) {
        numPlayerCards = players[playerIdx].tankPile.cardsPerColor[drawColor];
        numStealCards = players[stealIdx].tankPile.cardsPerColor[drawColor];

        for (i = 0; i < players[stealIdx].tankPile.cardsPerColor[drawColor]; i++) {
            players[playerIdx].tankPile.cards[drawColor][numPlayerCards] = players[stealIdx].tankPile.cards[drawColor][numStealCards - 1];
            ++numPlayerCards;
            --numStealCards;
        }

        players[playerIdx].tankPile.cardsPerColor[drawColor] = numPlayerCards;
        players[stealIdx].tankPile.cardsPerColor[drawColor] = numStealCards;

    } else {
        players[stealIdx].tankPile.cards[drawColor][0] = drawnCard;
        ++players[stealIdx].tankPile.cardsPerColor[drawColor];
    }

    return 1;
}

// Score

int scoreCard(Player players[], int playerIdx, Card drawnCard) {

    enum Color drawnColor = drawnCard.color;

    // check for cards

    int numPlayerCards = players[playerIdx].tankPile.cardsPerColor[drawnColor];

    if (numPlayerCards > 0) {
        int numScoreCards = players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX];

        int i;

        for (i = numPlayerCards - 1; i >= 0 ; i--) {
            players[playerIdx].tankPile.cards[SCORE_PILE_IDX][numScoreCards] = players[playerIdx].tankPile.cards[drawnColor][i];
            players[playerIdx].tankPile.cards[drawnColor][i] = (Card) {0};
            ++numScoreCards;
            --numPlayerCards;
        }

        players[playerIdx].tankPile.cardsPerColor[drawnColor] = numPlayerCards;
        players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX] = numScoreCards;
    } else {
        players[playerIdx].tankPile.cards[drawnColor][0] = drawnCard;
        ++players[playerIdx].tankPile.cardsPerColor[drawnColor];
    }

    // update score
    players[playerIdx].points = computePlayerScore(players[playerIdx].tankPile);

    return 1;
}


/* -------------------- */
/* SIMULATE PLAYER TURN */
// take players array, deck array, turn index, player action
// If steal,
// If score,

int simulatePlayerTurn(Player players[], int playerTurn, DrawPile *drawPile, enum Action playerAction) {

    Card drawnCard = drawCard(drawPile);

    if (playerAction == SCORE) {
        // if player chooses to score


    } else if (playerAction == STEAL) {
        // if player chooses to steal

        /* PLACE HOLDER INPUTS */
        int stealCardIdx;

        scanf("%d", &stealCardIdx);
        /* END OF PLACEHOLDER */

        stealCard(players, playerTurn, stealCardIdx, drawnCard);
    }


    return 0;
}



/* -------------- */
/* SIMULATE ROUND */

// Loop through players
// Call playerTurn()






/* ------------- */
/* SIMULATE GAME */

int playGame(DrawPile* drawPile, Player players[]) {

    // state vars for game condition
        // win bool
        // winner placeholder struct

    // initialize deck (randomized)

    // ROUND simulation loops while condition is not met
    return 1;
}

int debugGame(DrawPile* drawPile, Player players[], int playerCount) {

    /* INITIALIZE PLAYER */

    for (int b = 0; b < playerCount; b++)
        players[b] = (Player) {0};

    for (int a = 0; a < playerCount; a++) {
        populateDeck(drawPile, &players[a].tankPile);
    }

    /* Display cards */

    printf("DISPLAYING CARDS\n\n");
    for (int i = 0; i < drawPile->totalCards; i++) {

        printf("\nCard %d : \n", i);
        printf("\t color: %d\n", drawPile->cards[i].color);
        printf("\t back : %d %d %d\n", drawPile->cards[i].back[0], drawPile->cards[i].back[1], drawPile->cards[i].back[2]);
        printf("\t value: %d\n", drawPile->cards[i].value);
    }

    /* Display player info */

    printf("DISPLAYING PLAYER CARDS\n\n");
    for (int j = 0; j < playerCount; j++) {

        printf("\nPlayer %d : \n", j);

        // player cards
        // loop through each color

        for (int k = 0; k < 7; k++) {

            // loop for each color deck

            for (int z = 0; z < players[j].tankPile.cardsPerColor[k]; z++) {
                printf("\n\tCard %d %d: \n", k, z);
                printf("\t\t color: %d\n", players[j].tankPile.cards[k][z].color);
                printf("\t\t back : %d %d %d\n", players[j].tankPile.cards[k][z].back[0], players[j].tankPile.cards[k][z].back[1], players[j].tankPile.cards[k][z].back[2]);
                printf("\t\t value: %d\n", players[j].tankPile.cards[k][z].value);
            }
        }

    }

    return 1;
}

/* --------------- */
/* INITIALIZE GAME */

int initGame() {

    int playerCount, playerIdx;
    DrawPile drawPile = {0};

    /* INITIALIZE PLAYERS */

    printf("How many players? : ");
    scanf("%d", &playerCount);
    Player players[playerCount];

    StrName nameBuffer;

    playerIdx = 0;
    do {
        printf("P%d : ", (playerIdx + 1));
        scanf("%s", nameBuffer);
        bool duplicateFound = 0;

        /*** TEMPORARY ***/
        // check for duplicates
        for (int name = 0; name < playerIdx; name++) {
            if (strcmp(players[name].username, nameBuffer) == 0) {
                printf("Error: Name already listed; please try another name\n");
                duplicateFound = 1;
            }
        }
        if (!duplicateFound) {
            strcpy(players[playerIdx].username, nameBuffer);
            players[playerIdx].points = 0;
            playerIdx++;
        }
    } while (playerIdx < playerCount);

    /* LOAD DECK */

    FILE* mantisDeck = fopen("mantis.txt", "r");
    if (mantisDeck == NULL) {
        printf("Error: Could not load cards\n");
    } else {
        createDeck(mantisDeck, &drawPile);
        fclose(mantisDeck);
    }

    /* PLAY GAME */

    // playGame(&drawPile, players);
    debugGame(&drawPile, players, playerCount);

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
