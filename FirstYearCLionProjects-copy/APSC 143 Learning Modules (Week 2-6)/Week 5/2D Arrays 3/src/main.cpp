#include "password5.h"
#include <stdio.h>
#include <math.h>
/* Include the string library */

int main() {
    float wave1[2][15];
    int rowsize = sizeof(wave1[0]) / sizeof(wave1[0][0]);
    for(int i = 0; i < rowsize; i++) {
        wave1[0][i] = M_PI / 3 * i;
        wave1[1][i] = sin(wave1[0][i]);
    }

    float wave2[3][rowsize];
    for(int i = 0; i < rowsize; i++) {
        wave2[0][i] = wave1[0][i];
        wave2[1][i] = wave1[1][i];
        wave2[2][i] = cos(wave2[0][i]);
    }

    /* Declare wave3 array */
    printf("x\tsin\tcos\ttan\n");
    /* Copy wave2 using memcpy */
    for(int i = 0; i < rowsize; i++) {
        /* Initialize tan values in fourth row */
        printf("%.3f\t%.3f\t%.3f\t%.3f\n", wave3[0][i], wave3[1][i], wave3[2][i], wave3[3][i]);
    }
    completion(wave3[0][rowsize-3]);
}