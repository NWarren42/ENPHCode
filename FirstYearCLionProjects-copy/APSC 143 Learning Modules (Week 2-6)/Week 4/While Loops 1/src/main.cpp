#include <stdio.h>

int main() {
    int key, total;
    total = 0;
    while(key != 0) {
        printf("Enter an integer (0 to exit):\n");
        scanf("%d", &key);
        total += key;
    }
    printf("Total = %d\n", total);
}