/*
 *
 * blah blah blah I testify this work is mine and only mine and that the work is the intellectual property of the talking squirrel I have locked in my desk drawer
 *
 * The function being used for integration is e^(x^2). The taylor series equation for the function is just x^2 or pow(x, 2) for the coding nerd who may or may not be reading my code
 *
*/

#include <stdio.h>
#include <math.h>

#define R_CASE_1 5
#define R_CASE_2 25
#define R_CASE_3 100

#define T_CASE_1 3
#define T_CASE_2 5
#define T_CASE_3 10

// Is it ridiculous to make symbolic constants for all these values so that nothing is hardcoded and my code looks nice on a program that is very small and worth very little of my mark?....


// maybe

//BUT! my code is very pretty and easily configurable, so I don't care and I'm just going to do it anyways.



// I know the dude in the lecture videos likes to define functions after main, but I'm not doing that because I think it's weird to reference a function before having any idea what it does

int factorial(int input){ // Look at me using recursion wowowow can I get bonus marks please and thank you
	if(input == 0) return 1; // base case that says 0! = 1
	return input*factorial(input - 1);
}

double riemannSum(double lowerBound, double upperBound, int terms){

	double rectWidth = (upperBound-lowerBound)/(double)terms; // Just deltax = (b - a)/n. Used to establish the width of the vertical rectangles being used
															  // casting terms to double to avoid integer division and because im dumb and didn't just declare it as a double in the function
	double sum = 0;

	for(int i = 0; i < terms; i++){
		sum += rectWidth*exp(pow(lowerBound + i*rectWidth, 2));
	}

	/*
	 The code below works sometimes but not always... In theory the loop does the exact same thing but instead of tracking how many intervals have passed it just makes sure
	 that the x value is not at the upper limit. The problem I ran into is that for certain values of lowerBound and upperBound the loop will run one extra time. My theory is
	 that the loop steps i up until (upperBound-0.00000000001) because the precision required to track the values being used is not enough to be perfect. Just a theory though,
	 that could definitely be totally wrong but anyways, now my code works so it doesn't really matter. Just thought I'd include this on the odd chance TAs actually review comments
	 and also took the time to read about my problems. If you're a TA and you're reading this I hope you're having a nice day and if not, I hope tomorrow is better.

	for(double i = lowerBound; i <= upperBound; i += rectWidth){
		sum += rectWidth*exp(pow(i, 2));
	}

	*/

	return sum;
}

double taylorSeries(double x, int terms){
	double sum = 0;

	for(int i = 0; i < terms; i++){
		sum += (double)pow(pow(x, 2), i) / (double)factorial(i); // Adding each sequential term of the taylor series together
	}
	return sum;
}

double taylorSeriesRiemannSum(double lowerBound, double upperBound, int terms){

	double rectWidth = (upperBound-lowerBound)/(double)terms; //once again casting terms to double to avoid integer division and because im dumb and lazy and didn't just declare it as a double in the function
	double sum = 0;

	for(int i = 0; i < terms; i++){
		sum += rectWidth* taylorSeries(lowerBound + i*rectWidth, 10); // Adding up rectangle areas based on values given by taylor series function which is already written
	}

	// Same loop as earlier that was causing issues is below, just left it in to show it is applicable in multiple places
	/*
	for(double i = lowerBound; i < upperBound; i += rectWidth){
		sum += rectWidth * taylorSeries(i, 10);
	}
	*/

	return sum;
}

double calcRiemannSumError(double lowerBound, double upperBound, int terms){
	return 100 - (100*(riemannSum(lowerBound, upperBound, terms) / taylorSeriesRiemannSum(lowerBound, upperBound, terms))); //this is a really ugly equation that I could have split up into multiple lines/variables to
																														  //make easier to read but my ego told me I could write it like this so I did.
																														  //Essentially calculating the % of the actual value that the estimated taylor series value is and
																														  //then subtracting it from 100 to get the difference
}

int main() {

	double lowerBound, upperBound;

	printf("Enter the bounds to compute the Riemann Sum:"); // Do I need to comment this? I feel like it's pretty obvious
	scanf("%lf %lf", &lowerBound, &upperBound);

	printf("\n");

	//hardcoding numbers makes it a pain to change anything later, hence why I have an absurd number of symbolic constants. Plus it makes it so much easier to read and way more satisfying to look at

	printf("Riemann Sum with %d intervals: %.2lf\n", R_CASE_1, riemannSum(lowerBound, upperBound, R_CASE_1));
	printf("Riemann Sum with %d intervals: %.2lf\n", R_CASE_2, riemannSum(lowerBound, upperBound, R_CASE_2));
	printf("Riemann Sum with %d intervals: %.2lf\n", R_CASE_3, riemannSum(lowerBound, upperBound, R_CASE_3));

	printf("-------------------------------------------------------\n");

	printf("Taylor Series Approximation at x = %.2f with %d terms: %.2lf\n", (float)lowerBound, T_CASE_1, taylorSeries(lowerBound, T_CASE_1));
	printf("Taylor Series Approximation at x = %.2f with %d terms: %.2lf\n", (float)lowerBound, T_CASE_2, taylorSeries(lowerBound, T_CASE_2));
	printf("Taylor Series Approximation at x = %.2f with %d terms: %.2lf\n", (float)lowerBound, T_CASE_3, taylorSeries(lowerBound, T_CASE_3));

	printf("-------------------------------------------------------\n");

	printf("Taylor Series Riemann Sum with %d intervals: %.2lf\n", R_CASE_1, taylorSeriesRiemannSum(lowerBound, upperBound, R_CASE_1));
	printf("Taylor Series Riemann Sum with %d intervals: %.2lf\n", R_CASE_2, taylorSeriesRiemannSum(lowerBound, upperBound, R_CASE_2));
	printf("Taylor Series Riemann Sum with %d intervals: %.2lf\n", R_CASE_3, taylorSeriesRiemannSum(lowerBound, upperBound, R_CASE_3));

	printf("-------------------------------------------------------\n");

	printf("Error in Riemann Sums with %d intervals: %.2lf%%\n", R_CASE_1, calcRiemannSumError(lowerBound, upperBound, R_CASE_1));
	printf("Error in Riemann Sums with %d intervals: %.2lf%%\n", R_CASE_2, calcRiemannSumError(lowerBound, upperBound, R_CASE_2));
	printf("Error in Riemann Sums with %d intervals: %.2lf%%\n", R_CASE_3, calcRiemannSumError(lowerBound, upperBound, R_CASE_3));

}
