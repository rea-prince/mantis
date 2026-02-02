/******************************************************************************
 *  Description     : Game logic headers
 *  Author/s        : Alip, Rafael Prince Naif E.
 *  Section         : S12A
 *  Last Modified   : <date when last revision was made>
 ******************************************************************************/

#ifndef RAND_H // Include this to prevent redefinition error
#define RAND_H // Include this to prevent redefinition error

void initRandom();
int randomInt();
void shuffle(void *array, size_t n, size_t elem_size, unsigned int seed);

#endif // HELPERS_1_C; Include this to prevent redefinition error
