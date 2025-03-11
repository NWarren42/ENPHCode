#include <stdio.h>

int main() {
   /* Declare & initialize boggle */
   int pos;
   char key;
   while(1) {
       printf("Enter letter index & new letter:\n");
       scanf("%d %c", &pos, &key);
       if(/* pos must be a valid index */)
           /* Replace the letter */
       else
           break;
   }
   printf("Final word = \"%s\"\n", boggle);
}