/******************************************************************************
 *  Description     : This serves as the entry point of the program, calling all
 *                    necessary functions to run the game.
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A / S22
 *  Last Modified   : March 29, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

// gcc -Wall -std=c99 -Iinclude src/*.c -o build/mantis

/* ----- preprocessor directives ----- */

#include "common.h"
#include "models.h"

#include "menu.h"
#include "helpers.h"

#include "interface.h"
#include "display.h"

int main() {
    GameState game = {
        .randSeed = -1,
        .winningPoints = 20
    };
    PlayerRecord playerRecords[MAX_LOGGED_PLAYERS] = {0};
    int numPlayerRecords = 0;

    int menuInput;
    bool loadMenu = true;

    initRandom();

    /* LOOP MENU SCREEN FOR REPLAYABILITY */

    iClear(0,0,60,60);
    displayCustomHeader("You are now playing Mantis: CLI Edition!");

    /* LOAD PLAYERS FROM RECORDS */

    loadPlayerRecords(playerRecords, &numPlayerRecords);

    /* START MENU SCREEN */

    while (loadMenu) {

        displayMenuMain();

        getInput(&menuInput, EXIT_ACTION, N_MENU_Y, -1);

        if (menuInput == NEW_GAME) {

            newGame(&game, playerRecords, &numPlayerRecords);
            savePlayerRecords(playerRecords, numPlayerRecords);
            game = (GameState) {0};

        } else if (menuInput == TOP_PLAYERS) {

            topPlayers(playerRecords, numPlayerRecords);

        } else if (menuInput == GAME_SETTINGS) {

            gameSettings(&game);

        } else if (menuInput == EXIT_MENU) {

            loadMenu = false;
            savePlayerRecords(playerRecords, numPlayerRecords);

        }
        iClear(0,0,60,60);
    }

    return 0;
}

/**
 * This is to certify that this project is my/our own work, based on my/our personal
 * efforts in studying and applying the concepts learned. I/We have constructed the
 * functions and their respective algorithms and corresponding code by myself/ourselves.
 * The program was run, tested, and debugged by my/our own efforts. I/We further certify
 * that I/we have not copied in part or whole or otherwise plagiarized the work of other
 * students and/or persons, nor did I employ the use of AI in any part of the deliverable.
 *
 * Alip, Rafael Prince Naif E. (DLSU ID# 12504734)
 */
