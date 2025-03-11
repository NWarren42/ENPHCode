// APSC 143 Engineering Programming Project
// Program that runs the PacMan game using the 'W', 'A', 'S', 'D' characters.
// We attest that the code was written completely by the dream team (us).

// Include libraries
#include <cstdio>
#include "colours.h"
#include <conio.h>
#include <cstdlib>

// Define constants
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
#define START_DOTS 54
#define NUM_GHOSTS 2

// Initialize global variable
int dotCount = START_DOTS;

struct character{
	int x, y;
	int isOverDot;
	char displayCharacter;
	int colour;
};
typedef struct character entity;

void printColour(entity e){
	colourChange(e.colour);
	printf("%c  ", e.displayCharacter);
	colourChange(WHITE);
}

void printMap(char **map, entity pMan, entity g1, entity g2){
	system("cls");
	printf("\n");
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++) {
			if (j == g2.x && i == g2.y) printColour(g2);
			else if (j == g1.x && i == g1.y) printColour(g1);
			else if (j == pMan.x && i == pMan.y) printColour(pMan);
			else if (map[i][j] == WALL){
				colourChange(BLUE);
				printf("%c  ", map[i][j]);
				colourChange(WHITE);
			}
			else printf("%c  ", map[i][j]);
		}
		printf("\n");
	}
//    printf("\nDots Remaining: %d\n", dotCount);
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
	if(map[yPos][xPos] == DOT) return 1;
	else return 0;
}

void moveEntity(char** map, entity *e, char direction){
	if(e->isOverDot  == 1){
		map[e->y][e->x] = DOT;
	}else map[e->y][e->x] = EMPTY;
	if(direction == UP) e->y--;
	if(direction == DOWN) e->y++;
	if(direction == RIGHT) e->x++;
	if(direction == LEFT) e->x--;
	if(map[e->y][e->x] == DOT && (e->displayCharacter != PACMAN)) e->isOverDot = 1;
	else e->isOverDot = 0;
	map[e->y][e->x] = e->displayCharacter;
}

int movePac(char** map, entity *pMan){
	char c = (char)getch();

	if(c == UP && (map[pMan->y - 1][pMan->x] != WALL)) {
		if (map[pMan->y - 1][pMan->x] == DOT) {
			dotCount--;
		}
		moveEntity(map, pMan, UP);
		return 1;
	}else if(c == DOWN && (map[pMan->y + 1][pMan->x] != WALL)){
		if(map[pMan->y + 1][pMan->x] == DOT){
			dotCount--;
		}
		moveEntity(map, pMan, DOWN);
		return 1;
	}else if(c == RIGHT && (map[pMan->y][pMan->x + 1] != WALL)){
		if(map[pMan->y][pMan->x + 1] == DOT){
			dotCount--;
		}
		moveEntity(map, pMan, RIGHT);
		return 1;
	}else if(c == LEFT && (map[pMan->y][pMan->x - 1] != WALL)){
		if(map[pMan->y][pMan->x - 1] == DOT){
			dotCount--;
		}
		moveEntity(map, pMan, LEFT);
		return 1;
	}else return 0;
}
// Dijkstra recursion function
int dRec(int dMap[COLS][ROWS], int x, int y, entity *pMan){
	if (pMan->x == x && pMan->y == y) return 1; // Escape recursive function

	if (dMap[y][x] == -1) return 0;

	// If-statment to see if in dijkstra array
	if (dMap[y][x+1] > dMap[y][x]+1){ // Right
		dMap[y][x+1] = dMap[y][x]+1;
		dRec(dMap, x+1, y, pMan); // Recursive call
	}
	if (dMap[y][x-1] > dMap[y][x]+1){ // Left
		dMap[y][x-1] = dMap[y][x]+1;
		dRec(dMap, x-1, y, pMan); // Recursive call
	}
	if (dMap[y+1][x] > dMap[y][x]+1){ // Down
		dMap[y+1][x] = dMap[y][x]+1;
		dRec(dMap, x, y+1, pMan); // Recursive call
	}
	if (dMap[y-1][x] > dMap[y][x]+1){ // Up
		dMap[y-1][x] = dMap[y][x]+1;
		dRec(dMap, x, y-1, pMan); // Recursive call
	}
}
// Function to retrace the quickest route back to ghost from the pacman using the dijkstra map made in "moveGhost" function
char retrack(int dMap[COLS][ROWS], entity *pMan){
	// Initialize coordinates at position of pacMan
	int x = pMan->x, y = pMan->y;

	// While loop to go from pacmans position to 1 move away from the ghost in the quickest path
	while(dMap[y][x]>1){

		// If-statements to Trace back to the ghost in the direction with the smallest path
		if (dMap[y][x] > dMap[y][x+1] && dMap[y][x+1] >=0) x++;
		else if (dMap[y][x] > dMap[y][x-1] && dMap[y][x-1] >=0) x--;
		else if (dMap[y][x] > dMap[y+1][x] && dMap[y+1][x] >=0) y++;
		else if (dMap[y][x] > dMap[y-1][x] && dMap[y-1][x] >=0) y--;
		else printf("Alert! Alert! Major Tom has struck an error."); // In case of error
	}

	// If-statements to return direction which the ghost needs to go for the shortest route to pacMan
	if (dMap[y][x+1] == 0) return LEFT;
	if (dMap[y][x-1] == 0) return RIGHT;
	if (dMap[y+1][x] == 0) return UP;
	if (dMap[y-1][x] == 0) return DOWN;
	printf("Unfortunately the boss man has hit an error");
	return -1;
}
// Function to move ghost in the shortest path using dijkstra's algorithm
void moveGhost(char** map, entity* ghost, entity *pMan){
	// Create a new map of integers
	int dMap[COLS][ROWS];

	// For-loop to assign integers to each coordinate on the map
	for (int c = 0; c < COLS; c++){
		for (int r = 0; r < ROWS; r++){
			// If-statment to assign a -1 (a non-usable number) for walls or a 121 for any valid position on the map
			if (map[c][r] == WALL){
				dMap[c][r] = -1;
			}else{
				dMap[c][r] = COLS*ROWS;
			}
		}
	}
	// Assign 0 in the position of the ghost
	dMap[ghost -> y][ghost -> x] = 0;

	// Go through dijkstra's algorithm to find quickest path from ghost to pacMan
	dRec(dMap, ghost -> x, ghost -> y, pMan);

	// Move ghost one step towards the quickest path using the return of the dijkstra's algorithm recursion function
	moveEntity(map, ghost, retrack(dMap, pMan));
}
// Function to determine if the ghost is in the line of sight of the pacman (for the ghost who moves randomly)
int lineOfSight(char** map, entity* ghost, entity *pMan){
	if (ghost->x == pMan->x || ghost->y == pMan->y) return 1;
	return 0;
}
// Function to move ghost in random direction
void moveGhost2(char** map, entity* ghost, entity *pMan){
	// Initiallize variables determining which directions are clear
	int xClear = 0, yClear = 0;
	int xRight = 0, xLeft = 0, yUp = 0, yDown=0;
	// Creat random variables to chose specific direction
	int direction = rand() % (2);
	int way = rand() % (2);

	// If-statements to determine which directions are clear in the x-direction
	if (map[ghost->y][ghost->x + 1] != WALL) xRight = 1;
	if (map[ghost->y][ghost->x - 1] != WALL) xLeft = 1;
	if (xLeft+xRight >= 1) xClear = 1;

	// If-statements to determine which directions are clear in the y-direction
	if (map[ghost->y-1][ghost->x] != WALL) yUp = 1;
	if (map[ghost->y+1][ghost->x] != WALL) yDown = 1;
	if (yUp+yDown >= 1) yClear = 1;

	// If statements to check which routes it can go
	if (xClear == 1 && yClear == 1) {
		// If statements to follow the random choice of vertical or horizontal
		if (direction == 0){
			if (xRight == 1 && xLeft == 1){
				// Random left or right based on the random number
				if (way ==0) moveEntity(map, ghost, RIGHT);
				if (way ==1) moveEntity(map, ghost, LEFT);
			}
			else if (xRight == 1 && xLeft == 0) moveEntity(map, ghost, RIGHT); // Right
			else if (xLeft == 1 && xRight == 0) moveEntity(map, ghost, LEFT); // Left
		}
		else{
			if (yUp == 1 && yDown == 1){
				// Random up or down based on the random number
				if (way ==0)moveEntity(map, ghost, UP);
				if (way ==1)moveEntity(map, ghost, DOWN);
			}
			else if (yUp == 1 && yDown == 0) moveEntity(map, ghost, UP); // Up
			else if (yDown == 1 && yUp == 0) moveEntity(map, ghost, DOWN); // Down
		}
	} else if (xClear == 1 && yClear == 0) { // Only the horizontal path is clear
		if (xRight == 1 && xLeft == 1){
			// Random left or right based on the random number
			if (way ==0) moveEntity(map, ghost, RIGHT);
			if (way ==1) moveEntity(map, ghost, LEFT);
		}
		else if (xRight == 1 && xLeft == 0) moveEntity(map, ghost, RIGHT); // Right
		else if (xLeft == 1 && xRight == 0) moveEntity(map, ghost, LEFT); // Left

	} else if (xClear == 0 && yClear == 1) { // Only the vertical path is clear
		if (yUp == 1 && yDown == 1){
			// Random up or down based on the random number
			if (way ==0)moveEntity(map, ghost, UP);
			if (way ==1)moveEntity(map, ghost, DOWN);
		}
		else if (yUp == 1 && yDown == 0) moveEntity(map, ghost, UP); // Up
		else if (yDown == 1 && yUp == 0) moveEntity(map, ghost, DOWN); // Down
	}
}
int main() {

	entity pMan;
	pMan.displayCharacter = PACMAN;
	pMan.isOverDot = 0;
	pMan.colour = YELLOW;

	int ghostCount = 0;

	entity ghosts[NUM_GHOSTS];
	for(int i = 0; i < NUM_GHOSTS; i++){
		ghosts[i].isOverDot = TRUE;
		ghosts[i].displayCharacter = GHOST;
		if(ghostCount == 0) ghosts[ghostCount].colour = PINK;
		if(ghostCount == 1) ghosts[ghostCount].colour = PINK;
		ghostCount++;
	}

	int loss = FALSE;
	ghostCount = 0;

	// To open the "map.txt" file
	FILE* fp;
	fp = fopen("C:\\Users\\Noah\\CLionProjects\\apsc143project\\map.txt","r");

	// If-statement if file is not found
	if(fp == NULL){
		printf("File not found\n");
	}else {
		// Allocate memory for the array of the map.
		char **map = (char **) malloc(COLS * sizeof(char *));
		for (int i = 0; i < ROWS; i++) {
			map[i] = (char *) malloc(COLS * sizeof(char));

			// Add 'W' around the map
			if(i == 0 || i == ROWS - 1){
				for(int j = 0; j < COLS; j++){
					map[i][j] = 'W';
				}
				continue;
			}else {
				for (int j = 0; j < COLS; j++) {
					if (j == 0 || j == COLS - 1) {
						map[i][j] = 'W';
						continue;
					}
					// input map
					fscanf(fp, "%s", &map[i][j]);
					// Determine where pacMan is
					if (map[i][j] == PACMAN) {
						pMan.x = i;
						pMan.y = j;
					}
					// Determine where ghosts are
					if (map[i][j] == GHOST) {
						ghosts[0 + ghostCount].x = i;
						ghosts[0 + ghostCount].y = j;
						ghostCount++;
					}
				}
			}
		}
		// Print initial map
		printMap(map, pMan, ghosts[0], ghosts[1]);

		// While loop to play game until win or loss.
		while(TRUE){
			if(movePac(map, &pMan)){
				if(winCheck()){
					printMap(map, pMan, ghosts[0], ghosts[1]);
					printf("Congratulations! You win! ");
					system("pause");
					break;
				}
				for(int i = 0; i < NUM_GHOSTS; i++) {
					if (i==0) moveGhost(map, &ghosts[i], &pMan);
					if (i==1)
						if (lineOfSight(map, &ghosts[i], &pMan) == 1){
							moveGhost(map, &ghosts[i], &pMan);
						}else{
							moveGhost2(map, &ghosts[i], &pMan);
						}

					if (loseCheck(pMan, ghosts[i])) {
						printMap(map, pMan, ghosts[0], ghosts[1]);
						printf("Sorry, you lose. ");
						system("pause");
						loss = TRUE;
					}
				}
				// Print map
				printMap(map, pMan, ghosts[0], ghosts[1]);
			}


			// If lose leave the while loop
			if(loss) break;
		}
		free(map);
		fclose(fp);
	}
	return 0;
}

