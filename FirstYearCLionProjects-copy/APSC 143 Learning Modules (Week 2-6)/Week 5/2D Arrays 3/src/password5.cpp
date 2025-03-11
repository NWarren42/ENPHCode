//
// Created by bajd on 6/10/2022.
//
#include <stdio.h>
#include <math.h>
#include <string.h>

void completion(float x) {
    if (round(tan(x)) == 0){
        printf("Congratulations on completing the week 5 module!\n");
        printf("You should be all set for Assignment 5.\n");
        printf("Your password for the onQ completion quiz is \"Daybreak\".\n");
    }
}