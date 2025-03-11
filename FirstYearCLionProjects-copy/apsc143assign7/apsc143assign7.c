#include <stdio.h>
#include <stdlib.h>

/*  C:\\Users\\Noah\\CLionProjects\\apsc143assign7\\  */

/* I attest that the work in this project is solely completed by myself and is therefore my intellectual property
 *
 * I couldn't figure out how to make a 2d array of pointers, so instead I made a long 1D array subdivided into 3 pointer chunks instead and then worked with that using 3*n and corresponding offsets
 *
 */

#define NUM_COLUMNS 3

#define TOTAL_MASS_INDEX 0 // Any use of TOTAL_MASS_INDEX is irrelevant, it's just being used for clarity when reading the code so that you can understand what element of each chunk is being used
#define GRADE_INDEX 1
#define ORE_VALUE_INDEX 2

#define GOLD_PRICE 8500

int main() {

	int numPayloads;
	char tempString[10];


	FILE *fp;
	fp = fopen("payloads.txt", "r");

	if(fp == NULL){
		printf("File not found.\n");
	}else{
		numPayloads = (getc(fp) - '0'); //Converts ASCII character value to integer CHANGE THIS LATER

		double *payloadsArray[NUM_COLUMNS*numPayloads]; // Makes an array with enough entry space for 3 (NUM_COLUMNS) parameters per payload

		for(int i = 0; i < numPayloads*NUM_COLUMNS; i += NUM_COLUMNS){ //allocating space in memory for all the integers associated with each payload
			payloadsArray[i+TOTAL_MASS_INDEX] = (double*)malloc(sizeof(double));
			fscanf(fp, "%4s", tempString);
			*payloadsArray[i+TOTAL_MASS_INDEX] = strtod(tempString, NULL);

			payloadsArray[i+GRADE_INDEX] = (double*)malloc(sizeof(int));
			fscanf(fp, "%4s", tempString);
			*payloadsArray[i+GRADE_INDEX] = strtod(tempString, NULL);

			payloadsArray[i+ORE_VALUE_INDEX] = (double*)malloc(sizeof(int));
			*payloadsArray[i+ORE_VALUE_INDEX] = *payloadsArray[i+TOTAL_MASS_INDEX] * *payloadsArray[i+GRADE_INDEX] * GOLD_PRICE;
		}

		printf("Payload Data:\n");
		printf("Total Mass / Grade / Ore Value\n");
		for(int i = 0; i < numPayloads*NUM_COLUMNS; i+=NUM_COLUMNS){ // Output payload data read from the file
			printf("%4.0lf %3.2lf $%7.0lf\n", *payloadsArray[i+TOTAL_MASS_INDEX], *payloadsArray[i+GRADE_INDEX], *payloadsArray[i+ORE_VALUE_INDEX]);
		}

		double swap[NUM_COLUMNS];

		for(int i = numPayloads - 1; i > 0; i--){ // Insertion Sort Algorithm
			swap[TOTAL_MASS_INDEX] = *payloadsArray[NUM_COLUMNS * (i - 1)]; // Anything being multiplied by NUM_COLUMNS is just so that each chunk of 3 pointers in the array can stay related
			swap[GRADE_INDEX] = *payloadsArray[(NUM_COLUMNS * (i - 1)) + GRADE_INDEX];
			swap[ORE_VALUE_INDEX] = *payloadsArray[(NUM_COLUMNS * (i - 1)) + ORE_VALUE_INDEX];
			for(int j = i; j < numPayloads; j++){
				if(swap[ORE_VALUE_INDEX] < *payloadsArray[(NUM_COLUMNS * j) + ORE_VALUE_INDEX]){
					*payloadsArray[(NUM_COLUMNS * (j - 1)) + TOTAL_MASS_INDEX] = *payloadsArray[(NUM_COLUMNS * (j)) + TOTAL_MASS_INDEX];
					*payloadsArray[(NUM_COLUMNS * (j - 1)) + GRADE_INDEX] = *payloadsArray[(NUM_COLUMNS * (j)) + GRADE_INDEX];
					*payloadsArray[(NUM_COLUMNS * (j - 1)) + ORE_VALUE_INDEX] = *payloadsArray[(NUM_COLUMNS * (j)) + ORE_VALUE_INDEX];

					*payloadsArray[(NUM_COLUMNS * j) + TOTAL_MASS_INDEX] = swap[TOTAL_MASS_INDEX];
					*payloadsArray[(NUM_COLUMNS * j) + GRADE_INDEX] = swap[GRADE_INDEX];
					*payloadsArray[(NUM_COLUMNS * j) + ORE_VALUE_INDEX] = swap[ORE_VALUE_INDEX];
				}
			}
		}

		fclose(fp);

		fp = fopen("ores.txt", "w");

		fprintf(fp, "Sorted Payload Data:\n");
		fprintf(fp, "Total Mass / Grade / Ore Value\n");
		for(int i = 0; i < numPayloads*NUM_COLUMNS; i+=NUM_COLUMNS){
			fprintf(fp, "%4.0lf %3.2lf $%7.0lf\n", *payloadsArray[i+TOTAL_MASS_INDEX], *payloadsArray[i+GRADE_INDEX], *payloadsArray[i+ORE_VALUE_INDEX]);
		}

	}
}
