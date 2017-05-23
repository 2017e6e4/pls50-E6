// This assignment was quite difficult for me.
// To arrive at this result I received extensive guidance from a mathematician
// and a lot of help from a friend of mine who is a professional developer

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Player Struct
typedef struct PlayerGame{
	char name[17];
	int score;
	char id;
}Player;

// Cards Struct
typedef struct BoardGame{
	char colour;
	char shape;
	int number;
	char texture;
}Board;

void RandomBoard(Board b[3][4]);
int RandomInteger(int low, int high);
int checkDoubleCard(Board b[3][4], char c, char s, int n, char t);
void getNextCard(char *c, char *s, int *n, char *t);
void printBoard(Board b[3][4]);
void PlayerNames(Player *p, int n);
int CheckPlayer(Player *p, int n, char id);
int CheckSetCard(Board b[3][4], int x1, int y1, int x2, int y2, int x3, int y3);
int xyCoordinates(int xy);
int SetScore(Player *p, char choice, int n, int score, Player *wp);
void PrintInfo(Player *p, int n);

int main(){
	Player *p, winPlayer;
	Board b[3][4];

	int n, i, x1, y1, x2, y2, x3, y3 , win = 0, cp;
	char choice = '1';
	//color { r: red, g: green ,b: blue }
	//shape : { c: circle, t: triangle, r: rhombus }
	//number { 1,2,3 }
	//texture { b: filled, h: linned, e: empty }
	//[rt2e] : [2 red triangles empty ]

	// Random based on the time
	srand(time(NULL));

	// Inserting the amount of players
	printf("Please give the amount of players: ");
	scanf(" %d",&n);

	// Reserving memory for the players array
	p = (Player *)malloc(n*sizeof(Player));

	// Creating players
	PlayerNames(p,n);

	// Random cards
	RandomBoard(b);
	printf("\n-----Set Game-----\n");

	// Printing selected cards
	printBoard(b);
	printf("\n");

	// Termination if there is a winner or a player insertrs '0'
	while(choice != '0' && win == 0){
		printf("Give player id (");

		for(i=0;i<n;i++){
			printf("'%c',",p[i].id);
		}

		printf(") or '0' to terminate: ");

		// Reading the players selection
		scanf(" %c",&choice);

		// Checking the players ID
		cp = CheckPlayer(p,n,choice);

		// If wrong new cards are printed
		if(cp == 0){

			printf("Wrong choice. Try again.\nNew Random set of cards.\n");
			RandomBoard(b);
			printf("\n-----Set Game-----\n");
			printBoard(b);
			printf("\n");
		}

		// If correct the player gives the coordinates of 3 cards
		else if(cp == 1){

			//card1
			printf("Player with id '%c' choose first card:\n",choice);
			x1 = xyCoordinates(1);
			y1 = xyCoordinates(2);

			//card2
			printf("Player with id '%c' choose second card:\n",choice);
			x2 = xyCoordinates(1);
			y2 = xyCoordinates(2);

			//card3
			printf("Player with id '%c' choose third card:\n",choice);
			x3 = xyCoordinates(1);
			y3 = xyCoordinates(2);

			// Checking if the cards are a set
			if(CheckSetCard(b,x1,y1,x2,y2,x3,y3) == 1){

				printf("Correct Set of cards\n`");

				// Calculating the score
				win = SetScore(p,choice,n,2,&winPlayer);

				// Checking if there is a winner with 10 points
				if(win == 1){
					printf("the winner is o %s\n",winPlayer.name);
				}

				else{
					// New set of cards
					RandomBoard(b);
					printf("\n-----Set Game-----\n");
					printBoard(b);
					printf("\n");
				}
			}

			else{
				// Wrong set of cards. Removing points. Printing the same cards
				printf("Wrong Set of cards\n`");
				win = SetScore(p,choice,n,-1,&winPlayer);
				printf("\n-----Set Game-----\n");
				printBoard(b);
				printf("\n");
			}
		}
	}

	// Printing players info
	PrintInfo(p,n);

	return 1;
}

void PrintInfo(Player *p, int n){
	int i;

	// Printing infos for the players
	printf("-----Info for Players-----\n");

	for(i=0;i<n;i++){
		printf("%s %c %d\n",p[i].name,p[i].id,p[i].score);
	}
}

int SetScore(Player *p, char choice, int n, int score, Player *wp){
	int i=0, flag=0;

	// Calculating the score
	while(i < n && flag == 0){

		if(p[i].id == choice)
			flag = 1;

		else
			i++;
	}

	if(p[i].score + score >= 0)
		p[i].score = p[i].score + score;

	strcpy(wp->name,p[i].name);
	wp->id = p[i].id;
	wp->score = p[i].score;

	//eleghos an exei kerdisei h oxi

	if(p[i].score >= 10)
		return 1;	//winner

	else
		return 0;
}

int xyCoordinates(int xy){
	int i=-1;

	// Checking whether the coordinates are correct

	//x-coordinate
	if(xy == 1){
		while(i < 0 || i >= 3){
			printf("Give x coordinate: ");
			scanf(" %d",&i);

			if(i < 0 || i >= 3)
				printf("Wrong coordinates, give a number 0-2\n");
		}
	}

	//y-coordinate
	else if(xy == 2){
		while(i < 0 || i >= 4){
			printf("Give y coordinate: ");
			scanf(" %d",&i);

			if(i < 0 || i >= 4)
				printf("Wrong coordinates, give a number 0-3\n");
		}
	}

	return i;
}

int CheckSetCard(Board b[3][4], int x1, int y1, int x2, int y2, int x3, int y3){
	int i, j, ok = 0;

	// char colour, char shape, int number, char texture
	// Checking foe 3 cards set
	// Colour

	if((b[x1][y1].colour == b[x2][y2].colour) && (b[x1][y1].colour == b[x3][y3].colour))
		ok = 1;
	else if((b[x1][y1].colour != b[x2][y2].colour) && (b[x1][y1].colour != b[x3][y3].colour) && (b[x2][y2].colour != b[x3][y3].colour))
		ok = 1;
	else
		ok = 0;

	if(ok == 1){
		//shape
		if((b[x1][y1].shape == b[x2][y2].shape) && (b[x1][y1].shape == b[x3][y3].shape))
			ok = 1;
		else if((b[x1][y1].shape != b[x2][y2].shape) && (b[x1][y1].shape != b[x3][y3].shape) && (b[x2][y2].shape != b[x3][y3].shape))
			ok = 1;
		else
			ok = 0;
	}

	if(ok == 1){
		//number
		if((b[x1][y1].number == b[x2][y2].number) && (b[x1][y1].number == b[x3][y3].number))
			ok = 1;
		else if((b[x1][y1].number != b[x2][y2].number) && (b[x1][y1].number != b[x3][y3].number) && (b[x2][y2].number != b[x3][y3].number))
			ok = 1;
		else
			ok = 0;
	}

	if(ok == 1){
		//texture
		if((b[x1][y1].texture == b[x2][y2].texture) && (b[x1][y1].texture == b[x3][y3].texture))
			ok = 1;
		else if((b[x1][y1].texture != b[x2][y2].texture) && (b[x1][y1].texture != b[x3][y3].texture) && (b[x2][y2].texture != b[x3][y3].texture))
			ok = 1;
		else
			ok = 0;
	}

	return ok;
}

int CheckPlayer(Player *p, int n, char id){

	int i;

	// Checking if the id given belongs to a player
	if(id == '0')
		return -1;

	for(i=0;i<n;i++){
		if(p[i].id == id)
			return 1;
	}

	return 0;
}

void PlayerNames(Player *p, int n){

	int i;

	// Saving the players names and ids
	for(i=0;i<n;i++){
		printf("Please give the name of the player %d: ",i);
		scanf(" %s",p[i].name);

		printf("Please give the id of the player %d: ",i);
		scanf(" %c",&p[i].id);

		p[i].score = 0;
	}
}

void printBoard(Board b[3][4]){

	int i, j;

	// Printing the cards
	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			printf("[%c,%c,%d,%c] ",b[i][j].colour,b[i][j].shape,b[i][j].number,b[i][j].texture);
		}

		printf("\n");
	}
}

void RandomBoard(Board b[3][4]){

	int i, j, n;
	char c, s, t;

	// Selecting random cards

	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			b[i][j].colour = ' ';
			b[i][j].shape = ' ';
			b[i][j].number = 0;
			b[i][j].texture = ' ';
		}
	}

	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			do{
				getNextCard(&c,&s,&n,&t);
			}while(checkDoubleCard(b,c,s,n,t) == 0);

			b[i][j].colour = c;
			b[i][j].shape = s;
			b[i][j].number = n;
			b[i][j].texture = t;
		}
	}
}

int checkDoubleCard(Board b[3][4], char c, char s, int n, char t){
	int i, j;

	// Checking for double card selection
	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			if(b[i][j].colour == c && b[i][j].shape == s && b[i][j].number == n && b[i][j].texture == t)
				return 0;
		}
	}
	return 1;
}

void getNextCard(char *c, char *s, int *n, char *t){
	int r;

	// Selecting a random card

	// random colour
	r = RandomInteger(1,3);
	if(r == 1)
		*c = 'r';
	else if(r == 2)
		*c = 'g';
	else
		*c = 'b';

	//random shape
	r = RandomInteger(1,3);
	if(r == 1)
		*s = 'c';
	else if(r == 2)
		*s = 't';
	else
		*s = 'r';

	//random number
	*n = RandomInteger(1,3);

	//random texture
	r = RandomInteger(1,3);
	if(r == 1)
		*t = 'b';
	else if(r == 2)
		*t = 'h';
	else
		*t = 'e';
}

int RandomInteger(int low, int high){
	int k;
	double d;

	// Selecting a random number form low to high
	d = (double) rand() / ((double)RAND_MAX + 1);
	k = (int) (d * (high - low + 1));
	return (low + k);
}
