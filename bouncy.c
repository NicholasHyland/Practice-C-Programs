#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char * argv[]) {
	double percent = atof(argv[1]);			//takes in percent to find bouncy numbers up to that point
	
	int answer = findBouncy(percent);
	return 0;
}


int
findBouncy(double percent) {
	int count = 0;
	int number = 0;
	double percent2 = 0.000;
	
	while (percent2 != percent) {			//check the condition that the percentage is not greater than the input percent
		
		if (isBouncy(number) == 1) {		//check if it is bouncy, if so, increase the count
			count++;
		}		

		percent2 = (double) count/ (double) number; //the ratio is the count divided by the number we are at
		percent2 = percent2 * 100.00;
		if (percent2 >= percent) {			//if it's greater then we print the number
			printf("%d\n", number);
			break;
		}
		number++;
	}
	
	return 0;
}


int
isBouncy(int integer) {
	
	int increasing = 0;
	int decreasing = 0;
	
	int nextNumber;
	int lastNumber = integer % 10;				//get the last digit
	integer = integer / 10;					//remove the last digit
	
	while (integer > 0) {					//since we divide by 10 each time eventually it will get to 0 when we run out of numbers to compare
		nextNumber = integer % 10;			//get the last digit
		integer = integer / 10;				//remove the last digit
		if (nextNumber > lastNumber) {
			decreasing = 1;				//there contains a decrease in the number
		}
		else if (nextNumber < lastNumber) {
			increasing = 1;				//there contains an increase in the number
		}
		
		lastNumber = nextNumber;			//update the lastnumber to be the next number
		
		if (increasing && decreasing) {			//there is both an increase and decrease
			return 1;
		}
	}
	return 0;						//is not bouncy
}


