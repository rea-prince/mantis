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
 *
 *  @pre game points to an initialized GameState
 *  @pre drawnCard is a valid card
 */

int scoreCard(GameState* game, Card drawnCard) {

    enum Color drawnColor = drawnCard.color;
    int playerIdx = game->playerTurn;

    int numPlayerCards = game->players[playerIdx].tankPile.cardsPerColor[drawnColor];
    int numScoreCards;

    int i;
    int totalPts = 0;

    if (numPlayerCards > 0) {
        numScoreCards = game->players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX];

        for (i = numPlayerCards - 1; i >= 0 ; i--) {
            totalPts += game->players[playerIdx].tankPile.cards[drawnColor][i].value;
            game->players[playerIdx].tankPile.cards[SCORE_PILE_IDX][numScoreCards] = game->players[playerIdx].tankPile.cards[drawnColor][i];
            game->players[playerIdx].tankPile.cards[drawnColor][i] = (Card) {0};

            --game->players[playerIdx].tankPile.totalCards;
            ++numScoreCards;
            --numPlayerCards;
        }

        displayScoreCard(game, drawnColor, totalPts, playerIdx, game->players[playerIdx].tankPile.cardsPerColor[drawnColor]);

        game->players[playerIdx].tankPile.cardsPerColor[drawnColor] = numPlayerCards;
        game->players[playerIdx].tankPile.cardsPerColor[SCORE_PILE_IDX] = numScoreCards;
    } else {

        displayScoreCard(game, drawnColor, totalPts, playerIdx, numPlayerCards);

        game->players[playerIdx].tankPile.cards[drawnColor][0] = drawnCard;
        ++game->players[playerIdx].tankPile.cardsPerColor[drawnColor];
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
 *
 *  @pre game Points to a GameState that has been initialized
 *  @pre stealIdx is within the range of players and not equal to itself
 */

void stealCard(GameState* game, int stealIdx, Card drawnCard) {

    int numPlayerCards, numStealCards;
    int playerIdx = game->playerTurn;
    int i;

    enum Color drawnColor = drawnCard.color;
    if (game->players[stealIdx].tankPile.cardsPerColor[drawnColor] > 0) {

        // get current player and stealIdx player's number of cards

        numPlayerCards = game->players[playerIdx].tankPile.cardsPerColor[drawnColor];
        numStealCards = game->players[stealIdx].tankPile.cardsPerColor[drawnColor];

        // transfer cards from current player to stealIdx player

        for (i = 0; i < game->players[stealIdx].tankPile.cardsPerColor[drawnColor]; i++) {
            game->players[playerIdx].tankPile.cards[drawnColor][numPlayerCards] = game->players[stealIdx].tankPile.cards[drawnColor][numStealCards - 1];
            ++numPlayerCards;
            --numStealCards;
        }

        // append drawn card to current player's deck

        game->players[playerIdx].tankPile.cards[drawnColor][numPlayerCards] = drawnCard;
        ++numPlayerCards;

        displayStealCard(game, drawnColor, playerIdx, stealIdx);

        game->players[playerIdx].tankPile.cardsPerColor[drawnColor] = numPlayerCards;
        game->players[stealIdx].tankPile.cardsPerColor[drawnColor] = numStealCards;

    } else {
        displayStealCard(game, drawnColor, playerIdx, stealIdx);

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
 *
 *  @pre game Points to a GameState that has been initialized
 */

void takeTurn(GameState* game) {

    int playerAction;
    Card drawnCard;
    int stealCardIdx;

    if (game->drawPile.totalCards > 0) {

        displayInTurnInfo(game, &playerAction);

        drawnCard = drawCard(&game->drawPile);

        if (playerAction == SCORE) {

            displayDrawnCard(drawnCard);

            if (scoreCard(game, drawnCard) >= game->winningPoints) {
                game->winner = game->playerTurn;
                game->gameWon = true;
            }

        } else if (playerAction == STEAL) {

            displayInStealOptions(game, &stealCardIdx);
            displayDrawnCard(drawnCard);

            stealCard(game, stealCardIdx - 1, drawnCard);
        }

        game->playerTurn = (game->playerTurn + 1) % game->numPlayers;

    } else {

        /* DRAW */

        game->gameWon = true;
        game->winner = -1;
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
 *
 *  @pre game Points to a GameState that has been initialized
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
