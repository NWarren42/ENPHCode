#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main() {
	int rNum;

	for(int i = 0; i < 50; i ++){
		rNum = rand() % 3;
		printf("%d  ", rNum);
	}

}
