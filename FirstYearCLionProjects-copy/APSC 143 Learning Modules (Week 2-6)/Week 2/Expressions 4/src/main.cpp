#include <stdio.h>

int main() {
    int x1 = 3;
    int x2 = 3;

    x1 = x1 * 4;
    x2 *= 4;

    printf("x1 = %d, x2 = %d\n", x1, x2);
    return 0;
}