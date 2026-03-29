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
#include "logic.h"
#include "helpers.h"
#include "interface.h"

int main()
{
    int menuInput;
    bool loadMenu = true;

    GameState game = {0};
    game.randSeed = -1;
    game.winningPoints = 20;

    PlayerRecord playerRecords[MAX_LOGGED_PLAYERS] = {0};
    int numPlayerRecords = 0;

    initRandom();

    printf("You are now playing Mantis: CLI Edition!\n");

    /* LOOP MENU SCREEN FOR REPLAYABILITY */

    iClear(0,0,60,60);

    /* LOAD PLAYERS FROM RECORDS */

    loadPlayerRecords(playerRecords, &numPlayerRecords);

    /* START MENU SCREEN */

    while (loadMenu) {
        printf("+----------------------------------------------------------+\n");
        printf("| Main Menu                                                |\n");
        printf("+----------------------------------------------------------+\n");
        printf("| Welcome to Mantis: CLI Edition! Please select an option. |\n");
        printf("|    [1] New Game                                          |\n");
        printf("|    [2] Top Players                                       |\n");
        printf("|    [3] Game Settings                                     |\n");
        printf("|    [0] Exit and Save                                     |\n");
        printf("+----------------------------------------------------------+\n");

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
