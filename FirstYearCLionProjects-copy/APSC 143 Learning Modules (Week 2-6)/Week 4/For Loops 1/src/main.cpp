#include <stdio.h>

int main() {
    int loops;
    printf("Enter number of loops:\n");
    scanf("%d", &loops);
    for(int i = 0; i < loops; i++) {
        printf("Loop #%d\n", i + 1);
    }
}