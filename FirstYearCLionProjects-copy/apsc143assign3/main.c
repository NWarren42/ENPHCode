/*
I attest that this work is all my own (me = Noah Warren (his brain)) and not anyone else's. I was a little rusty on my circuit calculations so to help
me complete this assignment I consulted the website: https://www.allaboutcircuits.com/textbook/direct-current/chpt-5/simple-series-circuits/
as a resource to remind me of basic rules such as the fact that current remains the same across the whole circuit.
 */

#include <stdio.h>
#include <math.h>

#define SWITCH_ONE_ACTIVATION -0.7 // Voltage required for switch one to trip and close
#define SWITCH_TWO_ACTIVATION 6.4 // Voltage required for switch two to trip and close

#define LIGHTBULB_RESISTANCE 8 // The light bulb provides 9 ohms of resistance
#define RESISTOR_RESISTANCE 2 // The resistor provides 2 ohms of resistance

#define MIN_VALUE_ZERO -0.01 // Maximum negative voltage that is not treated as zero
#define MAX_VALUE_ZERO 0.01 // Minimum positive voltage that is not treated as zero

#define MIN_BULB_VOLTAGE 1 // Minimum activation voltage for the bulb is 1 volt
#define MAX_BULB_VOLTAGE 5.2 // Maximum activation voltage for the bulb is 5.2 volts

#define OPEN 0 // Switches are open when set to 0
#define CLOSED 1 // Switches are set to closed when set to 1

int main() {

	float timeElapsed; // Time since circuit was plugged in in seconds.

	float wallVoltage; // Voltage output from the wall at the given time
	float circuitCurrent; // Current remains constant across the whole
	float circuitResistance = LIGHTBULB_RESISTANCE + RESISTOR_RESISTANCE; // Circuit is in series so total resistance of the circuit is found by adding all resistances together

	float bulbVoltage;

	// True/false variable to track state of switch one. 0 means switch is open, 1 means switch is closed
	int switchOne = OPEN;
	int switchTwo = OPEN;
	// Both switches start in the open state

	// Getting user input for the time elapsed
	printf("Enter time in seconds: ");
	scanf("%f", &timeElapsed); // Save user input for seconds since activation

	/* 5:30pm
	Gradescope is a pain and doesn't use the return character after it enters a value in scanf like a human does when
	inputting a value, so I think printing a return character should fix it so the output is formatted properly.

	Stupid computers and their stupid shortcuts thinking they're better than us >:(
	 */

	printf("\n");

	// 5:35pm -- OKAY POST-NOTE ... That did not work. I will however be leaving it in because I think my point is still valid and it looks cleaner on Gradescope anyways :)

	// Voltage and current calculations
	wallVoltage = 8*(cosf(M_PI*timeElapsed)); // Using the provided equation to calculate the voltage output from the wall at the input time -- this is NOT 60Hz, what strange wall outlet is this
	circuitCurrent = wallVoltage/circuitResistance; // Rearranged Ohms law (V=IR) to calculate the current in the circuit. Since the circuit is in series the current is the same everywhere

	// Wall voltage and switch logic and outputs
	if(wallVoltage <= MIN_VALUE_ZERO){ // Checking if the voltage can be counted as a non-zero voltage from the negative side
		printf("Source voltage is negative\n");
		if(wallVoltage < SWITCH_ONE_ACTIVATION){ // Switch one trips at -.07 volts, this code checks if wall voltage is less than that
			switchOne = CLOSED; // Sets switch one to open
			printf("Switch 1 is closed\n");
		}
	} else if(wallVoltage >= MAX_VALUE_ZERO){ // Checking if the voltage can be counted as a non-zero voltage from the positive side
		printf("Source voltage is positive\n");
		if(wallVoltage > SWITCH_TWO_ACTIVATION){ // Switch two trips at 6.4 volts, this code checks if wall voltage is more than that
			switchTwo = CLOSED; // Sets switch two to open
			printf("Switch 2 is closed\n");
		}
	} else {
		printf("Source voltage is 0\n"); // If The source voltage is inside the range of values considered zero it is treated as 0
	}


	// Bulb voltage calculations and output
	if(switchOne || switchTwo) { // If either of the switches are closed, no current flows through the bulb so the voltage across the bulb is 0
		bulbVoltage = 0;
	} else {
		bulbVoltage = circuitCurrent * LIGHTBULB_RESISTANCE; // Since circuit current is already calculated and the resistance of the bulb is known, Ohm's law (V=IR) can be used to calculate the voltage across the bulb
	}
	printf("The Voltage of the bulb is %.2f V\n", bulbVoltage);


	// Bulb activation status check and output -- A better way to check if the bulb is on is to just look at it but I digress
	if (bulbVoltage <= MAX_BULB_VOLTAGE && bulbVoltage >= MIN_BULB_VOLTAGE) { // Bulb on/off indicator prints "bulb is on" if voltage is within bulb activation range
		printf("The bulb is on\n");
	} else {
		printf("The bulb is not on\n");
	}
}
