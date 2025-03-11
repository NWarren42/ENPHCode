#include <stdio.h>

int main() {
    char word[35];
    printf("Enter a sentence:\n");
    fgets(word, 35, stdin);
    printf("%s\n", word);
}