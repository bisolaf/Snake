#include "common.h"

#include <stdlib.h>


// Definition of global variables for game status.
int g_game_over;
int g_score;
int g_name_len;
char* g_name;



/** Sets the seed for random number generation.
 * Arguments:
 * 
 */
void set_seed(unsigned seed) {
    srand(seed);    
}

/** Returns a random index in [0, size)
 * Arguments:
 *  - `size`: the upper bound for the generated value (exclusive).
 */
unsigned generate_index(unsigned size) {
    return rand() % size;
}
