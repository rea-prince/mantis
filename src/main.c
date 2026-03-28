/******************************************************************************
 *  Description     : <short description of the project>
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : February 15, 2026
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

    PlayerRecord playerRecords[MAX_LOGGED_PLAYERS] = {0};
    int numPlayerRecords = 0;

    initRandom();

    printf("You are now playing Mantis: CLI Edition!\n");

    /* LOOP MENU SCREEN FOR REPLAYABILITY */

    iClear(0,0,60,60);

    /* LOAD PLAYERS FROM RECORDS */

    loadPlayerRecords(playerRecords, numPlayerRecords);

    /* START MENU SCREEN */

    while (loadMenu) {

        printf("+----------------------------------------------------------+\n");
        printf("| Main Menu                                                |\n");
        printf("+----------------------------------------------------------+\n");
        printf("|    [1] New Game                                          |\n");
        printf("|    [2] Top Players                                       |\n");
        printf("|    [3] Settings                                          |\n");
        printf("|    [0] Exit and Save                                     |\n");
        printf("+----------------------------------------------------------+\n");

        getMenuInput(&menuInput);

        if (menuInput == NEW_GAME) {
            newGame(playerRecords, &numPlayerRecords);
            savePlayerRecords(playerRecords, numPlayerRecords);
        } else if (menuInput == TOP_PLAYERS) {
            topPlayers(playerRecords, numPlayerRecords);
        } else if (menuInput == GAME_SETTINGS) {
            // TODO
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
