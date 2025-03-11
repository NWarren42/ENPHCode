#include <stdio.h>
/* Include the string library*/

int main() {
    char list[6][8] = {"Charlie",
                       "Bill",
                       "Sandra",
                       "Maurice",
                       "Julia",
                       "Yvette"};
    char temp[8];
    int x, y;
    while(1) {
        printf("Enter swap indexes:\n");
        scanf("%d %d", &x, &y);
        if(x == y || x >= 6 || x < 0 || y >= 6 || y < 0)
            break;
        /* Swap the names at indexes x and y */
    }
    printf("Final List Order:\n");
    for(int i = 0; i < 6; i++)
        printf("%s\n", list[i]);
}