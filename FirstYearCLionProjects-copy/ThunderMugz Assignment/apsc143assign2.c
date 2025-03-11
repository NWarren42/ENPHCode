#include <stdio.h>
#include <math.h>

#define GRAVITY 9.81 // acceleration from gravity is 9.81 m/s^2
#define MAX_FORCE_PER_STUDENT 300 // Each scrawny little engineering kid can support 300N of force
#define SEC_PER_MIN 60 // 60 seconds in a minute

int main() {

	// Mass Variables
	float boxSpringMass; // Box Spring Mass in kilograms
	float throneMass; // Throne mass in kilograms
	float totalMass; // Mass of box spring added to throne mass

	// Force Variables
	float netForce; // Total force of gravity exerted on the whole ThunderMugz in Newtons

	// Student Variables
	int studentsNeeded; // # of students needed to carry ThunderMugz. DON'T DROP YOUR NURSE

	// Time Variables
	int runTimeTot; // Time for entire run in seconds
	int runTimeMin; // Minutes the run will take to complete
	int runTimeSec; // Seconds the run will take to complete

	printf("Enter the mass of the box spring in kg:");
	scanf("%f", &boxSpringMass); // Storing the mass of the box spring input by user
	printf("Enter the mass of the throne in kg:");
	scanf("%f", &throneMass); // Storing the mass of the throne input by user


	// Calculations to figure out necessary students
	totalMass = boxSpringMass + throneMass; // Adding up total mass of the ThunderMugz
	netForce = totalMass * GRAVITY; // Force of gravity = mg  THANKS APPLE MAN (Newton)!!!!
	studentsNeeded = ceil(netForce/MAX_FORCE_PER_STUDENT); // Divides to find number of students required to support net mass of ThunderMugz but always rounds up. Can't have a fractional person and undershooting would be BAD

	// Calculations for time the run will take
	runTimeTot = (totalMass * (4 - exp(0.1 * (double)studentsNeeded))); // Equation provided in assignment outline gives time in seconds

	runTimeMin = floor(runTimeTot / SEC_PER_MIN); // Divide total seconds by sec/min to get minutes run takes and then always round down. Partial minutes are shown with seconds
	runTimeSec = runTimeTot - (runTimeMin * SEC_PER_MIN); // Subtracting the seconds elapsed in the whole minutes the run take from total seconds to get remaining seconds after the minutes have elapsed.

	printf("\nThe ThunderMugz will need a minimum of %i students to carry it.\n", studentsNeeded); // Outputting data for required students
	printf("It will take %i minutes and %i seconds to complete the ThunderMugz challenge.", runTimeMin, runTimeSec); // Outputting data for time the run will take

	return 0; // This is so unnecessary but idk if the grader wants it or nah
}
