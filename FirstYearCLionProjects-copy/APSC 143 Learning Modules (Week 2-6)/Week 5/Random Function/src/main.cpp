#include <stdio.h>
/* Include the standard library */

#define TRIALS 200
#define SIZE 50

int main() {
    /* Seed the random function */
    int randoms;
    int distribute[SIZE];
    for(int i = 0; i < SIZE; i++)
        distribute[i] = 0;
    for(int i = 0; i < TRIALS; i++) {
        /* Generate random value & count it in distribute */
    }
    for(int i = 0; i < SIZE; i++)
        printf("#%d: %d\n", i + 1, distribute[i]);
}