#include <stdio.h>
#include <math.h>

#define RATE_CONSTANT 0.0965

#define TIME_INTERVAL 0.01

#define MOLS_AMMONIA 4
#define MOLS_OXYGEN 3
#define MOLS_NITROGEN 2
#define MOLS_WATER 6

#define LOWEST_VALID_RATE 0.001

double reaction(double ammConc, double oxConc, double nitConc, double watConc, double checkConc){


	double rate = RATE_CONSTANT*ammConc*pow(oxConc, 2);


	if(rate < checkConc){
		printf("Final Reaction Molarities:\n");
		printf("NH3: %.2lf\n", ammConc);
		printf("O2:  %.2lf\n", oxConc);
		printf("N2:  %.2lf\n", nitConc);
		printf("H2O: %.2lf\n", watConc);
		return 0;
	}else reaction(, checkConc) + TIME_INTERVAL;

	return time;
}


int main() {

	float startAmmConc, startOxConc;

	printf("Enter initial ammonia and oxygen concentrations: ");
	scanf("%f %f", &startAmmConc, &startOxConc);

	reaction(startAmmConc, startOxConc, LOWEST_VALID_RATE);




}
