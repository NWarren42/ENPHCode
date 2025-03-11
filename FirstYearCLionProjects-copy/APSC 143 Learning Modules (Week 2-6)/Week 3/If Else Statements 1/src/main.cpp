#include <stdio.h>

int main() {
    int x, y;
    printf("Enter two different integers:\n");
    scanf("%d %d", &x, &y);

    if(x < y)
        printf("y is larger than x\n");
    else
        printf("x is larger than y\n");
}