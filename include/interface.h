/* Programmed by: Thomas Tiam-Lee
Description: This is a set of functions to help with the user interface for the machine project.
Last modified: AUG-15-2020
*/
#ifndef INTERFACE_H
#define INTERFACE_H

#ifdef _WIN32
void iMoveCursor(int x, int y);

void iClear(int x, int y, int width, int height);

void iHideCursor();

void iShowCursor();

void iSetColor(int color);

// For Linux and MacOS terminal
#else
/* This function moves the cursor to the given location on the
command line.
@param (int) x is the column index of the desired location
@param (int) y is the row index of the desired location
@return (void)
*/
void iMoveCursor(int x, int y);

/* This function clears a rectangular portion of the screen, and
moves the cursor to the top-left corner of the rectangle after
clearing.
@param (int) x is the column index of the top-left point of the rectangular portion.
@param (int) y is the row index of the top-left point of the rectangular portion.
@param (int) width is the width of the rectangle.
@param (int) height is the height of the rectangle.
@return (void)
*/
void iClear(int x, int y, int width, int height);

/* This function hides the cursor.
@return (void)
*/
void iHideCursor();

/* This function shows the cursor.
@return (void)
*/
void iShowCursor();

/* This function sets the color of any output statement
such as printf.
@param (int) color is an integer representing the desired color (refer to available color constants above).
@return (void)
*/
void iSetColor(int color);
#endif
#endif
