#include <stdio.h>

int main() {
    float debt = 12000;
    float payment = 2044.81;
    for(int months = 12; months > 0; months--) {
        debt *= 1.09; // compound interest
        /* breaking check here */
        debt -= payment;
        printf("Current debt: %.2f\n", debt);
    }
    printf("Debt repayed!\n");
}