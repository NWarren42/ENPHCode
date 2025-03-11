#include <stdio.h>
#include <math.h>

int main() {
    int pop = 100000;
    for(int i = 0; pop >= 0; i++) {
        pop *= pow(0.99, i);
        printf("New population: %d\n", pop);
    }
    printf("Population decimated\n");
}