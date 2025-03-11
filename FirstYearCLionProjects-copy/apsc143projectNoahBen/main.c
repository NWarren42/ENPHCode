// APSC 143 Engineering Programming Project Starter Code
// Feel free to change anything about this file, but do not remove "#include" "colours.h".

// Make sure to include all relevant libraries
#include <stdio.h>
#include "colours.h"
#include <conio.h>
#include <stdlib.h>

// You don't need to use these, but they help make your code look more organized
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

#define ROWS 11
#define COLS 11

#define START_DOTS 52
#define NUM_GHOSTS 2

// Below are the required functions for this program, but you will need to create your own as well.
// Make sure to specify the required parameters, if any.

int dotCount = START_DOTS;

struct character{
    int x, y;
    int isOverDot;
};

typedef struct character entity;

void printMap(char **map){

    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            printf("%c  ", map[i][j]);
        }
        printf("\n");
    }

}
int winCheck(){
    if(dotCount == 0){
        printf("You Win");
        return 1;
    }
    return 0;
}
int loseCheck(entity pMan, entity ghost){

    if ((pMan.x == ghost.x) && (pMan.y == ghost.y)) return 1;

    return 0;
}
int isWall(int xPos, int yPos, char **map){
    if(map[xPos][yPos] == WALL) return 1;
    else return 0;
}

int isDot(int xPos, int yPos, char **map){
    if(map[xPos][yPos] == DOT) return 1;
    else return 0;
}

int movePac(char** map, entity *pMan){
    char c = (char)getche();

    //getchar();
    if(c == UP && (map[pMan->y - 1][pMan->x] != WALL)) {
        if (map[pMan->y][pMan->x] == DOT) {
            dotCount--;
        }
        map[pMan->y][pMan->x] = EMPTY;
        pMan->y--;
        map[pMan->y][pMan->x] = PACMAN;
        return 1;
    }else if(c == DOWN && (map[pMan->y + 1][pMan->x] != WALL)){
        if(map[pMan->y][pMan->x] == DOT){
            dotCount--;
        }
        map[pMan->y][pMan->x] = EMPTY;
        pMan->y++;
        map[pMan->y][pMan->x] = PACMAN;
        return 1;
    }else if(c == RIGHT && (map[pMan->y][pMan->x + 1] != WALL)){
        if(map[pMan->y][pMan->x] == DOT){
            dotCount--;
        }
        map[pMan->y][pMan->x] = EMPTY;
        pMan->x++;
        map[pMan->y][pMan->x] = PACMAN;
        return 1;
    }else if(c == LEFT && (map[pMan->y][pMan->x - 1] != WALL)){
        if(map[pMan->y][pMan->x] == DOT){
            dotCount--;
        }
        map[pMan->y][pMan->x] = EMPTY;
        pMan->x--;
        map[pMan->y][pMan->x] = PACMAN;
        return 1;
    }else return 0;
}
void lineOfSight(char** map, entity* ghost, entity* pacMan){

}
/*void crossroadCheck(char** map, entity* ghost){
    int xClear = 0, yClear = 0;
    int xRight = 0, xLeft = 0, yUp = 0, yDown=0;
    if (ghost->x +1 != WALL || ghost->x -1 != WALL) {
        xClear = 1;
        if (ghost->x + 1 != WALL) {
            xRight = 1;
        }
        if (ghost->x - 1 != WALL) {
            xLeft = 1;
        }
    }
    if (ghost->y +1 != WALL || ghost->y -1 != WALL) {
        yClear = 1;
        if (ghost->y + 1 != WALL) {
            xRight = 1;
        }
        if (ghost->y - 1 != WALL) {
            xLeft = 1;
        }
    }

    if (xClear == 1 && yClear == 1){

    }else if (xClear == 1 && yClear == 0){
        if (xRight == 1 && xLeft == 1) {

        }else if (xRight == 1 && xLeft == 0) {

        }
        }else if (xRight == 1 && xLeft == 0) {

        }

    }else{

    }



}*/
void moveGhost(char** map, entity ghost){

}

int main() {

    entity pMan;
    entity ghosts[NUM_GHOSTS];

	int loss = FALSE;

    for(int i = 0; i < NUM_GHOSTS; i++){
        ghosts[i].isOverDot = TRUE;
    }

    FILE* fp;

    fp = fopen("C:\\Users\\Noah\\CLionProjects\\apsc143project\\map.txt","r");

    // If-statement if file is not found
    if(fp == NULL){
        printf("File not found\n");
    }else {

        int ghostCount = 0;

        char **map = (char **) malloc(COLS * sizeof(char *));

        for (int i = 0; i < COLS; i++) {
            map[i] = (char *) malloc(ROWS * sizeof(char));
            for (int j = 0; j < ROWS; j++) {
                fscanf(fp, "%s", &map[i][j]);
                if(map[i][j] == PACMAN){
                    pMan.x = i;
                    pMan.y = j;
                }
                if(map[i][j] == GHOST){
                    ghosts[0 + ghostCount].x = i;
                    ghosts[0 + ghostCount].y = j;
                    ghostCount++;
                }
            }
        }

        printMap(map);

        while(TRUE){
            if(movePac(map, &pMan)){
                printMap(map);
                for(int i = 0; i < NUM_GHOSTS; i++) {
                    if (loseCheck(pMan, ghosts[i])){
                        printf("Sorry, you lose. ");
                        system("pause");
                        loss = TRUE;
                    }
                }
                if(winCheck()){
                    printf("Congratulations! You win!");
                    system("pause");
                    break;
                }
            }


            if(loss) break;
        }
        free(map);
        fclose(fp);
    }

    return 0;
}
