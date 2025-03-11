/*
I attest to the originality of my work and it is my sole intellectual property

I LOVE ROCKS
*/

#include <stdio.h>

#define NUM_PARAMETERS 4

#define POROSITY 0
#define HYDRAULIC_CONDUCTIVITY 1
#define SPECIFIC_GRAVITY 2
#define FLOW_RATE 3

#define GRADIENT -0.725
#define CROSS_SECTIONAL_AREA 1200

int main() {

	int numLimestones;

	int locLowSG = 0;
	int locHighPO = 0;
	int locHighFR = 0;

	printf("Enter the number of limestones to compare:");
	scanf("%d", &numLimestones);

	double limestoneData[NUM_PARAMETERS][numLimestones];

	for(int i = 0; i < numLimestones; i++){ // GETTING INFO ABT EACH ROCK
		printf("Enter the porosity %%, hydraulic conductivity (m/s), and specific gravity for Limestone %d:\n", i + 1);
		scanf("%e %e %e", &limestoneData[POROSITY][i], &limestoneData[HYDRAULIC_CONDUCTIVITY][i], &limestoneData[SPECIFIC_GRAVITY][i]);
	}

	for(int i = 1; i < numLimestones; i++){ // FIND THE ROCK WITH LOWEST SPECIFIC GRAVITY
		if(limestoneData[SPECIFIC_GRAVITY][i] < limestoneData[SPECIFIC_GRAVITY][locLowSG]) locLowSG = i;
	}

	printf("The limestone with the lowest specific gravity is Limestone %d with a specific gravity of %.2lf\n", locLowSG + 1, limestoneData[SPECIFIC_GRAVITY][locLowSG]);


	for(int i = 0; i < numLimestones; i++){ // CALCULATING ALL FLOW VELOCITIES
		limestoneData[FLOW_RATE][i] = -1*limestoneData[HYDRAULIC_CONDUCTIVITY][i]*CROSS_SECTIONAL_AREA*GRADIENT;
	}

	printf("Flow Velocities:\n"); // OUTPUT ALL FLOW VELOCITIES
	for(int i = 0; i < numLimestones; i++){
		printf("Limestone %d: %.2lf cm^3/s\n", i + 1, limestoneData[HYDRAULIC_CONDUCTIVITY][i]);
	}

	for(int i = 1; i < numLimestones; i++){ // FIND THE ROCK WITH THE HIGHEST POROSITY
		if(limestoneData[POROSITY][i] > limestoneData[POROSITY][locHighPO]) locHighPO = i;
	}

	for(int i = 1; i < numLimestones; i++){ // FIND THE ROCK WITH THE HIGHEST FLOW VELOCITY
		if(limestoneData[FLOW_RATE][i] > limestoneData[FLOW_RATE][locHighFR]) locHighFR = i;
	}

	if(locHighPO == locHighFR) printf("The rock with the highest porosity has the highest flow velocity.");
	else printf("The rock with the highest porosity does not have the highest flow velocity.\n");
}
