#include <stdio.h>
#include <string.h>


int main() {
	printf("Hello, World!\n");

	int num;
	char character;
	float decimal;
	double longFloat;

	int userInt;
	char userStr[10]; // Defining an array creates an array with n elements where n is the number contained within square brackets.
					  // Array numbering starts at 0, so an array with 10 elements will have elements 0 through 9.

	switch (userInt) { // Only works with integer datatype. Can use ASCII characters e.g. case 'x': will execute code if the input is 'x'
		case 1:
			//code
			break;
		case 2:
			//code
			break;
		case 'x':
			//code
			break;
		default:
			//code to execute if input doesn't satisfy any of the cases
			break;
	}


	//Loops
	int counter = 10;
	int x;

	while(counter > 0){ // Same as while(counter) since any non 0 value is treated as true
		printf("%d", counter);
		counter--;
	}

	for(int i = 0; i < x; i++){ // Runs code inside loop x amount of times, using i as a counter for how many times code has been executed
		//code
		continue; // continue will skip remaining code and go to next cycle of the loop
		break; // Break will kick out of a loop
	}

	do{ // Runs code inside it so long as the expression in brackets is true -- key point is that it will always run at least once.
		// Do While loops check status of expression after the first time the code has been executed.
		//code
	}while(1);

	//Nested loop just means a loop inside a loop -- Used to run loops multiple times. Good for if you want slightly different input
	//to the loops

	//Arrays
	int intArr[x] = {1, 2, 3, 4}; // Makes an array with x elements and manually assigns values to the array starting at position 0
								  // This type of initialization must happen on the same line as the declaration statement

	intArr[0] = 23; // Individually assigns a value to one spot in the array.

	int TDintArr[x][x]; // Easiest to think of rows and columns. Essentially makes a table
}
