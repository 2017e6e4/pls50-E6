// This assignment would not have been made possible without the valuable
// guidance from a friend of mine who is working professionally as a developer


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Bus Struct
typedef struct BusSeats{
	char name[40];
	unsigned short telephone[10];
	unsigned int seat;
}Bus;

void openfile(Bus B[53], int *seats, char plate[8]);
void showemptyseats(Bus B[53], int seats);
void bookseat(Bus *book, char name[40], int tel[10]);
void searchbookseat(Bus B[53], int seats, int choice);
void cancelbook(Bus *cancel);
void showbookseats();
void savefile(Bus B[53], int seats, char plate[8]);

int main(){
	Bus B[53];
	int seats, i, j, choice = 1, s, choice2, telephone[10];
	char plate[8], firstname[40], lastname[40], tel[15];

	// Array B initialization. Array B contains the bus seats.
	for(i=0;i<53;i++){
		strcpy(B[i].name,"");
		B[i].seat = i+1;
		for(j=0;j<10;j++){
			B[i].telephone[j] = 0;
		}
	}

	// Opening text file bus.txt and registering the values in array B
	openfile(B,&seats,plate);


	// Loop runs until the user selects '0'
	while(choice != 0){

		printf("-----MENU----\n");
		printf("Please select a choice between 0-5\n");
		printf("1. Show empty seats & order the list of empty seats\n");
		printf("2. Book a specific seat\n");
		printf("3. Search if a seat is booked (with name or telephone)\n");
		printf("4. Cancel a booked seat\n");
		printf("5. Show a list of the booked seats ordered by the seat number\n");
		printf("0. Exit\n");
		scanf(" %d",&choice);


		// Exiting and printing array B to the file bus.txt
		if(choice == 0){

			savefile(B, seats, plate);
		}


        	// Displaying empty seats
		else if(choice == 1){

			showemptyseats(B,seats);
		}


		// Booking a seat
		else if(choice == 2){

			// Reading firstname lastname and telephone
			printf(" Please give the firstname: ");
			scanf(" %s",firstname);
			printf("Please give the lastname: ");
			scanf(" %s",lastname);
			printf("Please give the telephone: ");
			scanf(" %s",tel);

			strcat(lastname," ");
			strcat(lastname,firstname);

			for(j=0;j<10;j++){
				telephone[j] = tel[j] - '0';
			}

			// Reading the seat
			printf("Please give the seat number: ");
			scanf(" %d",&s);

			// Checking if the seat is within the bus seats limit
			if(s <= 0 || s > seats){
				printf("The seat you gave is out of range 1-%d\n",seats);
			}

			else{
				if(strcmp(B[s-1].name,"") == 0){
					// Seat booking
					bookseat(&B[s-1],lastname,telephone);
					printf("The seat is booked\n");
				}

				else{
					// Checking if the seat is already booked
					printf("The seat is already booked\n");
				}
			}
		}


		// Searching of a seat based on the name or the telephone
		else if(choice == 3){

			printf("Search a booked seat, 1 by name or 2 by telephone: ");
			scanf(" %d",&choice2);

			// 1 is for the name, 2 is for the telephone
			if(choice2 == 1 || choice2 == 2){
				// Searching for the booking
				searchbookseat(B,seats,choice2);
			}

			else{
				// Wrong choice
				printf("Wrong choice.\n");
			}
		}

		else if(choice == 4){

			// Reading the seat inserted by the user
			printf("Please give a seat: ");
			scanf(" %d",&s);

			// Checking if the seat is within the bus seats limit
			if(s <= 0 || s > seats){
				printf("The seat you give is out of range 1-%d\n",seats);
			}

			// Canceling of booking
			else{
				cancelbook(&B[s-1]);
				printf("The seat is canceled\n");
			}
		}

		// Printing of booked seats sorted by the seat number
		else if(choice == 5){

			showbookseats(B, seats);
		}

		// Printing error
		else{
			printf("Invalid choice. Please give a number between 0-5\n");
		}
	}

	exit(1);
}

void openfile(Bus B[53], int *seats, char plate[8]){
	int i, j, s, telephone[10];
	char firstname[40], lastname[40], tel[15];
	FILE *fp;

	// Reading the file bus.txt
	fp = fopen("bus.txt","r");

	if(fp == NULL){
		printf("The file is not open properly or not found\n");
		exit(-1);
	}

	// Reading the plate number from the file
	fscanf(fp,"%s",plate);

	// Reading the seats number from the file
	fscanf(fp,"%d",seats);

	// Printing of plate number and seat number of the bus
	printf("The plate number of the bus is %s\n",plate);
	printf("The bus has %d seats\n",*seats);


	// Saving the booked seats to the array B
	// Reading until the file is over
	while(fscanf(fp,"%s %s %d %s",lastname,firstname,&s,tel) != EOF){

		// Copying of all the fields to the respective position of array B
		strcpy(B[s-1].name,lastname);
		strcat(B[s-1].name," ");
		strcat(B[s-1].name,firstname);
		B[s-1].seat = s;

		// Transforming the telephone
		for(j=0;j<10;j++){
			B[s-1].telephone[j] = tel[j] - '0';
		}
	}

	// Closing file
	fclose(fp);
}

void showemptyseats(Bus B[53], int seats){
	int i, count=0;

	// Going through array B to find how many and who are the empty seats
	printf("Empty seats are: ");

	for(i=0;i<seats;i++){

		if(strcmp(B[i].name,"") == 0){
			printf("%d ",B[i].seat);
			count++;
		}
	}
    // Printing the result
	printf("\nTotal empty seats are %d\n",count);
}

void bookseat(Bus *book, char name[40], int tel[10]){

    //Bus B[53], int seats, Bus book)

	int i;

	strcpy(book->name,name);
	for(i=0;i<10;i++){
		book->telephone[i] = tel[i];
	}

	/*

	int i, j, flag=0;

	strcpy(B[book.seat-1].name,book.name);
	for(i=0;i<10;i++){
		B[book.seat-1].telephone[i] = book.telephone[i];
	}

	*/
}

void searchbookseat(Bus B[53], int seats, int choice){

	char lastname[40], firstname[40], telephone[15];
	int tel[10], i, j, flag;

	// Searching based on the name
	if(choice == 1){
		printf(" Please give a lastname: ");
		scanf(" %s", lastname);
		printf("Please give a firstname: ");
		scanf(" %s", firstname);
		strcat(lastname," ");
		strcat(lastname,firstname);

		for(i=0;i<seats;i++){
			if(strcmp(B[i].name,lastname) == 0){
				printf("Seat %d is already booked by name %s\n",i+1,lastname);
				return;
			}
		}

		printf("Name %s has not booked a seat\n");
	}

	// Searching based on the telephone
	else if(choice == 2){

		printf("Please give a telephone: ");
		scanf("%s", telephone);

		for(i=0;i<10;i++){
			tel[i] = telephone[i]-'0';
		}

		for(i=0;i<seats;i++){
			flag = 0;

			for(j=0;j<10;j++){
				if(tel[j] == B[i].telephone[j]){
					flag++;
				}
			}

			if(flag == 10){
				printf("Seat %d is already booked by name %s\n",i+1,B[i].name);
				return;
			}
		}

		printf("Name %s has not booked a seat\n");
	}
}

void cancelbook(Bus *cancel){

	int i;

	strcpy(cancel->name,"");
	for(i=0;i<10;i++){
		cancel->telephone[i] = 0;
	}
}

void showbookseats(Bus B[53], int seats){

	int i, j;

	printf("Booked seats are: \n");

	for(i=0;i<seats;i++){
		if(strcmp(B[i].name,"") != 0){
			printf("%s ",B[i].name);

			for(j=0;j<10;j++){
				printf("%d",B[i].telephone[j]);
			}

			printf(" %d\n",B[i].seat);
		}
	}
}

void savefile(Bus B[53], int seats, char plate[8]){

	int i, j;
	FILE *fp;

	// Printing results to the file bus.txt
	fp = fopen("bus.txt","w");

	if(fp == NULL){
		printf("The file is not open properly or not found\n");
		exit(-1);
	}

	fprintf(fp,"%s\n",plate);
	fprintf(fp,"%d\n",seats);

	for(i=0;i<seats;i++){
		if(strcmp(B[i].name,"") != 0){
			fprintf(fp,"%s %d ",B[i].name,B[i].seat);

			for(j=0;j<10;j++){
				fprintf(fp,"%d",B[i].telephone[j]);
			}

			fprintf(fp,"\n");
		}
	}

	fclose(fp);
}
