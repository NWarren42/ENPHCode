#include <stdio.h>
#include <math.h>

int main() {
    float x = 4.108;
    float y = 13.95;
    int result = (x * 6 + 11) / 3 >= pow(y, 2) / 8 - 7.5;
    printf("Result is %d\n", result);
}