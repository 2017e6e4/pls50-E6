// This is a program that calculates the reverse binary equivalent
// of a decimal number inserted by the user

#include <stdio.h>
#include <stdlib.h>

int main(){
	int number = 0;
	int const div = 2;
	char c;

	// Validation: The user keeps inserting numbers until the number is >0
	// If not, then there is an error message and a reminder that the number must be >0
	while(number <= 0){

		printf("Please insert a number that is greater than zero (>0): ");
		scanf(" %d",&number);

		if(number <= 0){
			printf("Error! The number must be > 0\n");
		}
	}

	// Calculating the reverse binary equivalent of the number inserted
	while(number > 0){
		c = (number%div == 1) ? '1': '0';
		putchar(c);
		number = number / div;
	}

	exit(1);
}
