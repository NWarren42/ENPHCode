//
// Created by bajd on 5/30/2022.
//
#include "password4.h"
#include <stdio.h>

void completion (int i, int upTo){
    if(upTo % i == 0){
        printf("Congratulations on completing the week 4 module!\n");
        printf("You should be all set for Assignment 4.\n");
        printf("Your password for the onQ completion quiz is \"Seventeen\".\n");
    }
}