/******************************************************************************
 *  Description     : Definitions of all information needed for file persistence
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef PERSISTENCE_H // Include this to prevent redefinition error
#define PERSISTENCE_H // Include this to prevent redefinition error

/******************************************************************************
 * NOTE: These definitions are placed here in defs.h to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

#define PI 3.1415
#define ARR_SIZE 10

/**
 * Represents a 2D point
 */
typedef struct
{
  int x; // The x-coordinate of a point
  int y; // The y-coordinate of a point
} Coordinate;

/**
 * Represents a date
 */
typedef struct
{
  int day;   // The day [1-31]
  int month; // The integer representation of the month [1-12]
  int year;  // The year
} Date;

#endif // DEFS_H; Include this to prevent redefinition error
