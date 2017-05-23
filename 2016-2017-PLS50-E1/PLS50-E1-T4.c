// This is a very basic booking system for a bus

#include <stdio.h>
#include <stdlib.h>

int main(){

    // Variable declarations
	int Bus[53], i, seats, N, option = 1, count = 0, booking;
	FILE *fp;
	char plate[8];


	// Array initialization. Seats represented with 0 are the ones available
	for(i=0;i<53;i++){
		Bus[i] = 0;
	}

	// The file bus.txt is read
	fp = fopen("bus.txt","r");
	if(fp == NULL){
		printf("The file with the bus details has not been opened properly or was not found\n");
		exit(-1);
	}

	// Reading the licence plate number of the bus
	fscanf(fp,"%s",plate);
	// Reading the amount of seats from the file
	fscanf(fp,"%d",&seats);
	// Presenting the findings to the user
	printf("The licence plate of the bus is %s\n",plate);
	printf("This particular bus has %d seats\n",seats);
	// Closing of the file
	fclose(fp);

	// Validation. The amount of seats must follow the 4*N+53 rule
	// In any other case there is an error message and the program is terminated
	N = (seats - 5) / 4;
	if((seats > 53) || (seats != ((4*N)+5))){
		printf("Invalid amount of seats\n");
		exit(-1);
	}

	// Options menu presented to the user every time
	while(option != 0){

		printf("-----MENU----\n");
		printf("Please select one of the following options 0-8\n");
		printf("0. Exit\n");
		printf("1. See the available seats\n");
		printf("2. Book a specific seat\n");
		printf("3. Find the first seat next to a window\n");
		printf("4. Cancel the booking of a seat\n");
		printf("5. Search if a seat is booked\n");
		printf("6. See the seats already booked \n");
		printf("7. See the seat layout of the bus\n");
		printf("8. Save the seat layout of the bus in a file named 'layout.txt'\n");
		scanf(" %d",&option);

		if(option == 0){
			exit(1);
		}

		// Option '1'. The user is presented with all the available seats
		else if(option == 1){
			count = 0;
			printf("The available seats are: ");
			for(i=0;i<seats;i++){
				if(Bus[i] == 0){
					printf("%d ",i+1);
					count++;
				}
			}
			printf("\nThe bus has %d available seats\n",count);
		} // End of option 1

		// Option '2'. The user is asked to select a seat for booking
		else if(option == 2){
			printf("Please insert the number of the seat you would like to book: ");
			scanf(" %d",&booking);

			// Validation. The seat number inserted must be inside the seats range of the particular bus
			if(booking <= 0 || booking > seats){
				printf("The seat number of your choice must be between 1 and %d\n",seats);
			}

			else{
				// Validation of whether the seat is already booked or not.
				if(Bus[booking-1] == 0){
					Bus[booking-1] = 1;
				}
				else{
					printf("Unfortunately this seat is already booked\n");
				}
			}
		} // End of option 2

		// Option '3'. The program  finds the first available seat next to a window.
		else if(option == 3){

			i = 0;
			count = 0;
			// Finding out which of the seats are next to a window
			while((i < seats-5) && (count == 0)){
				if(Bus[i] == 0){
					count = i+1;
				}
				else if(Bus[i+3] == 0){
					count = i+1;
				}
				i = i+4;
			}

			if(count == 0){
				if(Bus[i] == 0){
					count = i+1;
				}
				else if(Bus[i+4] == 0){
					count = i+1;
				}
			}

			// Finding out whether there a available seats next to a window
			if(count != 0){
				printf("The first available seat next to a window is %d\n",count);
			}
			else{
				printf("Unfortunately there is no seat available next to a window\n");
			}
		} // End of option 3

		// Option '4'. Canceling of a booking
		else if(option == 4){
			printf("Can you please share with us the number of the seat you would like to cancel: ");
			scanf(" %d",&booking);

			// Validation. The seat number inserted must be inside the seats range of the particular bus
			if(booking <= 0 || booking > seats){
				printf("The seat number of your choice has to be between 1 and %d\n",seats);
			}
			else{
				// Validation. The seat must be available
				if(Bus[booking-1] == 1){
					Bus[booking-1] = 0;
				}
				else{
					printf("The seat is not booked\n");
				}
			}
		} // End of option 4

		// Option '5'. Checking if a seat number inserted by the user is booked or not
		else if(option == 5){

			printf("Let us know of the seat number you want to check if it is booked or not: ");
			scanf(" %d",&booking);
			// Validation. The seat number inserted must be inside the seats range of the particular bus
			if(booking <= 0 || booking > seats){
				printf("The number of your choice has to be between 1 and %d\n",seats);
			}

			else{
				// Checking whether the seat is booked or not
				// Presenting the user with the answer
				if(Bus[booking-1] == 1){
					printf("Sorry, this seat is booked\n");
				}
				else{
					printf("This seat is available\n");
				}
			}
		} // End of option 5

		// Option '6' presents the seats that are booked
		else if(option == 6){
			printf("The seats currently booked are: ");
			for(i=0;i<seats;i++){
				if(Bus[i] == 1){
					printf("%d ",i+1);
				}
			}
			printf("\n");
		} // End of option 6

		// Option '7'. Printing the seats layout of the bus
		else if(option == 7){
			printf("%s\n",plate);
			count = 0;

			for(i=0;i<seats-5;i++){

				if((i > 0) && (i%2 == 0)){
					printf(" ");
				}

				if((i > 0) && (i%4 == 0)){
					printf("\n");
				}

				// Every seat booked is represented with an asterisk (*)
				if(Bus[i] == 1){
					printf("*");
				}

				// Every seat that is avalable is represented with an underscore (_)
				else{
					printf("_");
				}
			} // End for

			// Printing of the last 5 seats of the bus
			printf("\n");
			for(i=seats-5;i<seats;i++){
				if(Bus[i] == 1){
					printf("*");
				}
				else{
					printf("_");
				}
			}
			printf("\n\n");
		} // End of option 7

		// Printing the bus layout in the document called layout.txt
		// Similar to the way it was done in option 7
		// Opening of the document
		else if(option == 8){
			fp = fopen("layout.txt","w");

			if(fp == NULL){
				printf("The file is not open properly or not found\n");
				exit(-1);
			}

			fprintf(fp,"%s\n",plate);
			count = 0;

			for(i=0;i<seats-5;i++){
				if((i > 0) && (i%2 == 0)){
					fprintf(fp," ");
				}

				if((i > 0) && (i%4 == 0)){
					fprintf(fp,"\n");
				}

				if(Bus[i] == 1){
					fprintf(fp,"*");
				}
				else{
					fprintf(fp,"_");
				}
			}

			fprintf(fp,"\n");

			for(i=seats-5;i<seats;i++){
				if(Bus[i] == 1){
					fprintf(fp,"*");
				}
				else{
					fprintf(fp,"_");
				}
			}

			// Closing the file
			fclose(fp);
			printf("The bus layout was saved in the document named 'layout.txt'\n");

		} // End of option 8

		// Case where the user has selected a number out of the options range
		else{
			printf("Invalid selection. Please choose the number between 0-8 that corresponds to the action you would like to take:\n");
		}

	}// End of options loop

	exit(1);
}
