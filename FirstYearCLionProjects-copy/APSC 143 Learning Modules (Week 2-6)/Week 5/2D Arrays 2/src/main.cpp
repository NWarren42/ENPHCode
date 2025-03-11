#include <stdio.h>

#define SIZE 12

int main() {
    int timesTable[SIZE][SIZE];
    for(/* outer loop arguments */) {
        for(/* inner loop arguments */) {
            timesTable[row][col] = /* Multiplication here */;
            printf("%d\t", timesTable[row][col]);
        }
        printf("\n");
    }
}