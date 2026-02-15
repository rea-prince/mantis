/******************************************************************************
 *  Description     : Headers for helper.c
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef HELPERS_C
#define HELPERS_C

int searchName(char list[MAX_LOGGED_PLAYERS][MAX_NAME_CHARS], char* key, int playerCount);
int createDeck(FILE* mantisDeck, Card gameDeck[]);

#endif
