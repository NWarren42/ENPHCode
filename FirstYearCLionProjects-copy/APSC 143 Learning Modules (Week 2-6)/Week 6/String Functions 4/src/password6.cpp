//
// Created by bajd on 6/10/2022.
//
#include <stdio.h>
#include <string.h>

int completion(char phrase[]) {
    if(!strcmp(phrase, "a green lobster will dig the lecture ")){
        printf("Congratulations on completing the week 6 module!\n");
        printf("You should be all set for Assignment 6.\n");
        printf("Your password for the onQ completion quiz is \"Furnace\".\n");
        return 1;
    }
    return 0;
}