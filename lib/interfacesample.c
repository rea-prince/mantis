/* Programmed by: Thomas Tiam-Lee
Description: This is an example program demonstrating how to use interface.h
Last modified: AUG-15-2020
*/

#include <stdio.h>
#include "interface.c"

int main()
{
  char str[100];
  iClear(0, 0, 100, 30);
  printf("--------------------\n");
  printf("--------------------\n");
  printf("--------------------\n");
  printf("--------------------\n");
  printf("--------------------\n");
  printf("--------------------\n");
  printf("You should be seeing six lines of white dashes\n");
  printf("Press any key...\n");
  getchar();

  iClear(0, 0, 100, 8);
  iSetColor(I_COLOR_RED);
  printf("--------------------\n");
  iSetColor(I_COLOR_YELLOW);
  printf("--------------------\n");
  iSetColor(I_COLOR_GREEN);
  printf("--------------------\n");
  iSetColor(I_COLOR_CYAN);
  printf("--------------------\n");
  iSetColor(I_COLOR_BLUE);
  printf("--------------------\n");
  iSetColor(I_COLOR_PURPLE);
  printf("--------------------\n");
  iSetColor(I_COLOR_WHITE);
  printf("The white dashes should have been replaced by different colors per line\n");
  printf("Press any key...\n");
  getchar();

  iClear(0, 6, 100, 2);
  iHideCursor();
  iMoveCursor(0, 6);
  printf("You should not be seeing the cursor now.\n");
  printf("Press any key...\n");
  getchar();

  iClear(0, 6, 100, 2);
  printf("Type a short word. It should appear in the hole\n");
  printf("Type a short word and press enter...\n");
  iClear(7, 2, 6, 1);
  scanf("%s", str);

  iClear(0, 0, 100, 8);
  iShowCursor();

  return 0;
}
