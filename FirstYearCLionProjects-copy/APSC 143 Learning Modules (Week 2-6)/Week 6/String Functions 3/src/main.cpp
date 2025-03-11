#include <stdio.h>
/* Include the string library */

int main() {
    char test[] = "tangerine";
    char user[30];
    printf("Enter string:\n");
    scanf("%s", &user);
   /* Compare the strings & store in comp */
    if(/* Check value of comp */)
        // test = user
        printf("The same!\n");
    else if(/* Check value of comp */)
        // test > user
        printf("%s before %s\n", user, test);
    else
        // test < user
        printf("%s before %s\n", test, user);
}