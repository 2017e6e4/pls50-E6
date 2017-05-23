// This program calculates the perimeter of one of 4 specific shapes square, rectangle, triangle, circle

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float square_perimeter(float length);
float rectangle_perimeter(float length, float width);
float triangle_perimeter(float a, float b);
float circle_perimeter(float r);

int main(){
	int option = 1;
	float a, b, perimeter;

	// The user is presented with an options menu
	while(option != 0){
		printf("-----MENU-----\n");
		printf("Please make a selection between options 0-4\n");
		printf("0. Exit\n");
		printf("1. Square\n");
		printf("2. Rectangle\n");
		printf("3. Triangle\n");
		printf("4. Circle\n");
		scanf(" %d",&option);

		// If the user selection is '0' the program ends
		if(option == 0){
			exit(1);
		}

		// If the user has selected '1' as an option
		// there is a prompt to insert the length of the side of a square
		// The square side is inserted and read, the perimeter is calculated and printed
		else if(option == 1){
			printf("Please insert the length of the side of the square: ");
			scanf(" %f",&a);
			perimeter = square_perimeter(a);
			printf("The square perimeter is %f\n",perimeter);
		}

		// If the user has selected '2' as an option
		// there is a prompt to insert the length and the width of the rectangle
		// The length and the width are inserted and read, the perimeter is calculated and printed
		else if(option == 2){
			printf("Please insert the length of the rectangle: ");
			scanf(" %f",&a);
			printf("Please insert the width of the rectangle: ");
			scanf(" %f",&b);
			perimeter = rectangle_perimeter(a,b);
			printf("The rectangle perimeter is %f\n",perimeter);
		}

		// If the user has selected '3' as an option
		// there is a prompt to insert the length of the triangle sides
		// The length of the triangle sides are inserted and read, the perimeter is calculated and printed
		else if(option == 3){
			printf("Please insert the length of the first side of the triangle: ");
			scanf(" %f",&a);
			printf("Please insert the length of the second side of the triangle: ");
			scanf(" %f",&b);
			perimeter = triangle_perimeter(a,b);
			printf("The triangle perimeter is %f\n",perimeter);
		}

		// If the user has selected '4' as an option
		// there is a prompt to insert the radius of the circle
		// The radius is inserted and read, the perimeter is calculated and printed
		else if(option == 4){
			printf("Please insert the radius of the circle: ");
			scanf(" %f",&a);
			perimeter = circle_perimeter(a);
			printf("The circle perimeter is %f\n",perimeter);
		}

		// In any other case the user is presented with an error message
		// and then prompted to insert an option inside the available range
		else{
			printf("Wrong selection. Please give it another try selecting exclusively one of the options 0-4 above\n");
		}
	}

	exit(1);
}

//Function that calculates the perimeter of a square
float square_perimeter(float length)
{
	float perimeter;
	perimeter = 4.0*length;
	return(perimeter);
}

//Function that calculates the perimeter of a rectangle
float rectangle_perimeter(float length, float width)
{
	float perimeter;
	perimeter = (2.0*length) + (2.0*width);
	return(perimeter);
}

//Function that calculates the perimeter of a triangle
float triangle_perimeter(float a, float b)
{
	float perimeter, c;
	c = sqrt(pow(a,2) + pow(b,2));
	perimeter = a + b + c;
	return(perimeter);
}

//Function that calculates the perimeter of a circle
float circle_perimeter(float r)
{
	float perimeter, pi = 3.14;
	perimeter = 2.0*r*pi;
	return(perimeter);
}
