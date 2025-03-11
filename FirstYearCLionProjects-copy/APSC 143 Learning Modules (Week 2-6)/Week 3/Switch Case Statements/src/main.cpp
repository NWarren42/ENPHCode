#include <stdio.h>

int main() {
    char key = 'a';
    switch(key) {
        case 'a':
            printf("Apples\n");
        case 'b':
            printf("Bananas\n");
        case 'g':
            printf("Grapefruit\n");
        case 'm':
            printf("Mangoes\n");
        default:
            printf("Fresh out of fruit\n");
    }
}