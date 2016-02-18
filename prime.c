#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[]) {	//char ** argv
	//int n;
	//printf("Enter integer: ");
	//scanf("%d", &n);
	int number = atoi(argv[1]);           //take in argument for number to calculate up to for primeDivisors
	int result = primeGenerating(number); //result is the sum of all numbers that match the condition
	printf("%d \n", result);
	return 0;

}

int
primeGenerating(int integer) {
	int count = 0;
	int i;
	for (i = 1; i <= integer; i++) {
		if (findDivisors(i) == 1) {	//if the number fits the findDivisors then add to count
			count += i;
		}
	}
	return count;
} 

int
isPrime(int integer) {
	int i;
	for (i = 2; i <= (integer/2) + 1; i++){ //only need to go up to integer/2 + 1 because beyond that it will never divide evenly
		if ((integer % i) == 0) {	//integer is not a prime because it divides evenly
			return 0;
		}
	} 
	return 1;				//integer is a prime
}

int
findDivisors(int integer) {
/*	double i = 2.0;
	while (i <= sqrt(integer)){
		int myInt = (int)i;
		if ((integer % myInt) == 0) {
			int checkPrime = myInt + (integer/myInt);
			if (isPrime(checkPrime) == 0) {		//(divisor + (integer/divisor)) is not a prime
				return 0;
			}
			if (myInt != (integer/myInt)){
				int checkPrime2 = (integer/myInt) + (integer/(integer/myInt));
				if (isPrime(checkPrime) == 0) {
					return 0;
				}
			}
		}
	i++;
	}	
	return 1;						//all (divisor + (integer/divisor)) is a prime */
	
	int i = 1;
	while (i <= (integer/2)) {
		if ((integer % i) == 0) {
			int checkPrime = i + (integer/i); //checking the prime condition
			if (isPrime(checkPrime) == 0) {   //it's not a prime
				return 0;
			}
		}
		i++;
	}
	return 1;					  //all divisors fit the condition
}




