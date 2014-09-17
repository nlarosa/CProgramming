// CSE 20211
//
// computer.c
//
// This program allows for one user (Player X) to play the game 
// Othello against a computer opponent (Player O). The user and 
// computer must place "soldiers" on a board, trying to trap enemy 
// "soldiers" between their own. Further instructions are available 
// upon loading the game.
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BOARD_SIZE 8			// this is a macro for our board size

// first, function declarations (prototypes)

void initializeBoard(char x[BOARD_SIZE][BOARD_SIZE]);						// prototypes for dealing with the game board
void configureBoard(char x[BOARD_SIZE][BOARD_SIZE]);
void displayBoard(char x[BOARD_SIZE][BOARD_SIZE]);
int checkBoard(char x[BOARD_SIZE][BOARD_SIZE]);

char getPlayer(int turnNumber);									// prototypes for determining the player status
char getOpposingPlayer(int turnNumber);

void getInput(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber);					// prototypes for checking input and winners
void checkWinner(char x[BOARD_SIZE][BOARD_SIZE]);	

void checkMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);		// prototypes for checking adjacency with moves
void checkMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);

int makeMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);			// prototypes for determining surrounding enemies
int makeMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int makeMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int makeMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int makeMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int makeMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);

int checkCaptureLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);		// prototypes for finding groups of enemies
int checkCaptureUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int checkCaptureUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int checkCaptureUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int checkCaptureRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int checkCaptureDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int checkCaptureDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);
int checkCaptureDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row);

int makeFlipsLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);	// prototypes for making the flips once group found
int makeFlipsUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);
int makeFlipsUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);
int makeFlipsUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);
int makeFlipsRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);
int makeFlipsDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);
int makeFlipsDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);
int makeFlipsDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row);

// computer player specific prototypes

void AImove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber);							// prototypes for determining the best computer move
int AIrank(char x[BOARD_SIZE][BOARD_SIZE], int column1, int row1, int column2, int row2);

int AIcheckMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);				// prototypes for checking adjacency with moves
int AIcheckMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
int AIcheckMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
int AIcheckMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
int AIcheckMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
int AIcheckMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);

// now for function definitions

void initializeBoard(char x[BOARD_SIZE][BOARD_SIZE])			// this function initializes the game board with all '.'
{									// the dimension of our board is fixed, so no size parameter needed
	int row = 0;            					// keeping track of rows and columns of the game board
        int col = 0;

        for( row = 0; row < BOARD_SIZE; row++ )
        {
                for( col = 0; col < BOARD_SIZE; col++ )
                {	
			x[row][col] = '.';
                }
        }
}

void configureBoard(char x[BOARD_SIZE][BOARD_SIZE])			// this function establishes the beginning configuration of the game board
{
	x[(BOARD_SIZE/2)-1][(BOARD_SIZE/2)-1] = 'X';
	x[(BOARD_SIZE/2)-1][BOARD_SIZE/2] = 'O';
	
	x[BOARD_SIZE/2][(BOARD_SIZE/2)-1] = 'O';
	x[BOARD_SIZE/2][BOARD_SIZE/2] = 'X';
}

void displayBoard(char x[BOARD_SIZE][BOARD_SIZE])			// this function displays the game board
{									// complete with numeric labels of rows and columns
	int row = 0;
	int col = 0;

	printf("\n\t ");

	for( row = 0; row < BOARD_SIZE; row++ )				// printing the first row of column numbers
	{
		if( BOARD_SIZE > 10 && row <= 10 )	printf("  %d", row);	// make sure columns are lined up if labels are more than two digits  
		else 					printf(" %d", row);
	} 

	printf("\n");
	
	for( row = 0; row < BOARD_SIZE; row++ )				// for every iteration of row number, we will iterate through all columns
        {								// which will create the first row
		printf("\t%d ", row);					// the first column is every row should be the row number

                for( col = 0; col < BOARD_SIZE; col++ )
                {
			if( BOARD_SIZE > 10 )				// meaning some column and row labels will be two digits
			{
				if( row < 10 && col == 0 )		printf(" %c ", x[row][col]);	
				else if( row >= 10 && col == 0 )	printf("%c ", x[row][col]);
				else					printf(" %c ", x[row][col]);	
			}
			else
			{
				printf("%c ", x[row][col]);
			}
		}	
	
                printf("\n");
        }

	printf("\n");
}

int checkBoard(char x[BOARD_SIZE][BOARD_SIZE])				// this function checks to see if the board is complete or not
{
	int row = 0;
	int col = 0;
	
	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			if( x[row][col] == '.' )
			{
				return 1;				// returns true, the board is not complete and the game continues
			}
		}
	}

	return 0;							// returns false, the board is complete and the game is over
}

//

char getPlayer(int turnNumber)						// this function retrieves the current player based on the turn number
{
	if( (turnNumber % 2) == 0 )					// 'O' player will play on the even number turns
	{
		return 'O';
	}
	else								// 'X' player will play on the odd number turns
	{
		return 'X';
	}
}

char getOpposingPlayer(int turnNumber)					// this function retrieves the current opposing player
{
	if( (turnNumber % 2) == 0 )					// 'X' player will be opposing player on even number turns
	{
		return 'X';
	}
	else								// 'O' player will be opposing player on odd number turns
	{
		return 'O';
	}
}

//

void getInput(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber)		// this function retrieves the user's move and checks for errors
{
	int colNum = 0;
	int rowNum = 0;

	printf("Player %c moves: ", getPlayer(turnNumber));
	
	if( scanf("%d %d", &colNum, &rowNum) != 2 )
	{
		while( getchar() != '\n' ) continue;			// clears buffer of wrong input 
		printf("Please enter integer coordinates only.\n");
		getInput(x, turnNumber);				// ask the user again if their input is not valid
	}
	else
	{
		checkMove(x, turnNumber, colNum, rowNum);
	}
}

void checkMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks to make sure the user makes a valid move
{
	if( column < 0 || column >= BOARD_SIZE )					// move must be within board bounds
	{
		printf("Specify a column between 0 and %d.\n", BOARD_SIZE-1);
		getInput(x, turnNumber);	
	}
	else if( row < 0 || row >= BOARD_SIZE )						// move must be within board bounds
	{
		printf("Specify a row between 0 and %d.\n", BOARD_SIZE-1);
		getInput(x, turnNumber);
	}
	else if( x[row][column] != '.' )						// move must be in unoccupied space
	{
		printf("Choose an unoccupied space.\n");
		getInput(x, turnNumber);
	}

	if( row == 0 )									// now we need to make sure moves are adjacent to other soldiers	
	{
		checkMoveTop(x, turnNumber, column, row);				// we know the move is in top row of board
	}
	else if( row == (BOARD_SIZE-1) )
	{
		checkMoveBottom(x, turnNumber, column, row);				// we know the move is in bottom row of board
	}
	else if( column == 0 )
	{
		checkMoveLeft(x, turnNumber, column, row);				// we know the move is in left-most column of board
	}
	else if( column == (BOARD_SIZE-1) )
	{
		checkMoveRight(x, turnNumber, column, row);				// we know the move is in right-most column of board
	}
	else
	{
		checkMoveMid(x, turnNumber, column, row);				// we know the move is in the middle of the board
	}
}

void checkMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for adjacency with moves in top row
{
	int adjacent = 0;								// this boolean is true if piece is adjacent to any other

	if( x[row+1][column] != '.' )
	{
		adjacent = 1;								// there is a player downwards
	}

	if( column != 0 )
	{
		if( x[row][column-1] != '.' )
		{
			adjacent = 1;							// there is a player to the left
		}
		
		if( x[row+1][column-1] != '.' )
		{
			adjacent = 1;							// there is a player to the lower-left
		}
	}		

	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] != '.' )
		{
			adjacent = 1;							// there is a player to the right
		}
		if( x[row+1][column+1] != '.' )
		{
			adjacent = 1;							// there is a player to the lower-right
		}
	}

	if( adjacent == 1 )
	{
		makeMove(x, turnNumber, 0, column, row);
	}
	else
	{
		printf("Your soldier must be placed adjacent to another.\n");
		getInput(x, turnNumber);
	}
}

void checkMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)// this function checks for adjacency with moves in bottom row
{
	int adjacent = 0;								// this boolean is true if piece is adjacent to any other

	if( x[row-1][column] != '.' )
	{
		adjacent = 1;								// there is a player upward
	}

	if( column != 0 )
	{
		if( x[row][column-1] != '.' )
		{
			adjacent = 1;							// there is a player to the left
		}
		if( x[row-1][column-1] != '.' )
		{
			adjacent = 1;							// there is a player to the upper-left
		}
	}
	
	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] != '.' )
		{
			adjacent = 1;							// there is a player to the right
		}	
		if( x[row-1][column+1] != '.' )
		{
			adjacent = 1;							// there is a player to the upper-right
		}
	}

	if( adjacent == 1 )
	{
		makeMove(x, turnNumber, 0, column, row);
	}
	else
	{
		printf("Your soldier must be placed adjacent to another.\n");
		getInput(x, turnNumber);
	}
}

void checkMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for adjacency with moves in left-most column 
{
	int adjacent = 0;								// this boolean is true if piece is adjacent to any other

	if( x[row][column+1] != '.' )
	{
		adjacent = 1;								// there is a player to the right
	}

	if( row != 0 )
	{
		if( x[row-1][column+1] != '.' )
		{
			adjacent = 1;							// there is a player to the upper-right
		}
		if( x[row-1][column] != '.' )
		{
			adjacent = 1;							// there is a player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column+1] != '.' )
		{
			adjacent = 1;							// there is a player to the lower-right
		}
		if( x[row+1][column] != '.' )
		{
			adjacent = 1;							// there is a player downwards
		}
	}

	if( adjacent == 1 )
	{
		makeMove(x, turnNumber, 0, column, row);
	}
	else
	{
		printf("Your soldier must be placed adjacent to another.\n");
		getInput(x, turnNumber);
	}
}

void checkMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)// this function checks for adjacency with moves in right-most column
{
	int adjacent = 0;								// this boolean is true if piece is adjacent to any other

	if( x[row][column-1] != '.' )
	{
		adjacent = 1;								// there is a player to the left
	}

	if( row != 0 )
	{
		if( x[row-1][column-1] != '.' )
		{
			adjacent = 1;							// there is a player to the upper-left
		}
		if( x[row-1][column] != '.' )
		{
			adjacent = 1;							// there is a player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column-1] != '.' )
		{
			adjacent = 1;							// there is a player to the lower-left
		}
		if( x[row+1][column] != '.' )
		{
			adjacent = 1;							// there is a player downwards
		}
	}

	if( adjacent == 1 )
	{
		makeMove(x, turnNumber, 0, column, row);
	}
	else
	{
		printf("Your soldier must be placed adjacent to another.\n");
		getInput(x, turnNumber);
	}
}

void checkMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function check for adjacency with moves in the middle of the board
{
	int adjacent = 0;								// this boolean is true if piece is adjacent to any other

	if( x[row][column-1] != '.' )
	{
		adjacent = 1;								// there is a player to the left
	}
	if( x[row][column+1] != '.' )
	{
		adjacent = 1;								// there is a player to the right
	}
	if( x[row+1][column] != '.' )
	{
		adjacent = 1;								// there is a player downwards
	}
	if( x[row+1][column-1] != '.' )
	{
		adjacent = 1;								// there is a player to the lower-left
	}
	if( x[row+1][column+1] != '.' )
	{
		adjacent = 1;								// there is a player to the lower-right
	}
	if( x[row-1][column] != '.' )
	{
		adjacent = 1;								// there is a player upwards
	}
	if( x[row-1][column-1] != '.' )
	{
		adjacent = 1;								// there is an opposing player to the upper-left
	}
	if( x[row-1][column+1] != '.' )
	{
		adjacent = 1;								// there is an opposing player to the upper-right
	}

	if( adjacent == 1 )
	{
		makeMove(x, turnNumber, 0, column, row);
	}
	else
	{
		printf("Your soldier must be placed adjacent to another.\n");
		getInput(x, turnNumber);
	}
}

//

int makeMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function makes changes to the game board and checks position
{												// and passes along total flips made
	char current = getPlayer(turnNumber);
	
	x[row][column] = current;

	if( row == 0 )
	{
		//printf("%d flips made.\n", makeMoveTop(x, turnNumber, comp, column, row));
		return (makeMoveTop(x, turnNumber, comp, column, row));			// we know the move is in top row of board
	}
	else if( row == (BOARD_SIZE-1) )
	{
		//printf("%d flips made.\n", makeMoveBottom(x, turnNumber, comp, column, row));
		return (makeMoveBottom(x, turnNumber, comp, column, row));		// we know the move is in bottom row of board
	}
	else if( column == 0 )
	{
		//printf("%d flips made.\n", makeMoveLeft(x, turnNumber, comp, column, row));
		return (makeMoveLeft(x, turnNumber, comp, column, row));		// we know the move is in left-most column of board
	}
	else if( column == (BOARD_SIZE-1) )
	{
		//printf("%d flips made.\n", makeMoveRight(x, turnNumber, comp, column, row));
		return (makeMoveRight(x, turnNumber, comp, column, row));		// we know the move is in right-most column of board
	}
	else
	{
		//printf("%d flips made.\n", makeMoveMid(x, turnNumber, comp, column, row));
		return (makeMoveMid(x, turnNumber, comp, column, row));			// we know the move is in the middle of the board
	}
}

int makeMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for flips with moves in top row
{												// and passes along total flips made
	char opposing = getOpposingPlayer(turnNumber);

	int sum = 0;									// this is the sum of flips made by each of the captures made

	if( x[row+1][column] == opposing )
	{
		sum += (checkCaptureDown(x, turnNumber, comp, column, row+1));		// there is an opposing player downward
	}

	if( column != 0 )
	{
		if( x[row][column-1] == opposing )
		{
			sum += (checkCaptureLeft(x, turnNumber, comp, column-1, row));		// there is an opposing player to the left
		}
		
		if( x[row+1][column-1] == opposing )
		{
			sum += (checkCaptureDnLeft(x, turnNumber, comp, column-1, row+1));	// there is an opposing player to the lower-left
		}
	}		

	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] == opposing )
		{
			sum += (checkCaptureRight(x, turnNumber, comp, column+1, row));		// there is an opposing player to the right
		}
		if( x[row+1][column+1] == opposing )
		{
			sum += (checkCaptureDnRight(x, turnNumber, comp, column+1, row+1));	// there is an opposing player to the lower-right
		}
	}

	return sum;
}

int makeMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for flips with moves in bottom row
{													// and passes along total flips made
	char opposing = getOpposingPlayer(turnNumber);

	int sum = 0;									// this is the sum of flips made by each of the captures made

	if( x[row-1][column] == opposing )
	{
		sum += (checkCaptureUp(x, turnNumber, comp, column, row-1));			// there is an opposing player upward
	}

	if( column != 0 )
	{
		if( x[row][column-1] == opposing )
		{
			sum += (checkCaptureLeft(x, turnNumber, comp, column-1, row));		// there is an opposing player to the left
		}
		if( x[row-1][column-1] == opposing )
		{
			sum += (checkCaptureUpLeft(x, turnNumber, comp, column-1, row-1));	// there is an opposing player to the upper-left
		}
	}
	
	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] == opposing )
		{
			sum += (checkCaptureRight(x, turnNumber, comp, column+1, row));		// there is an opposing player to the right
		}	
		if( x[row-1][column+1] == opposing )
		{
			sum += (checkCaptureUpRight(x, turnNumber, comp, column+1, row-1));	// there is an opposing player to the upper-right
		}
	}

	return sum;
}

int makeMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)		// this function checks for flips with moves in left-most columN
{													// and passes along total flips made
	char opposing = getOpposingPlayer(turnNumber);

	int sum = 0;									// this is the sum of flips made by each of the captures made

	if( x[row][column+1] == opposing )
	{
		sum += (checkCaptureRight(x, turnNumber, comp, column+1, row));			// there is an opposing player to the right
	}

	if( row != 0 )
	{
		if( x[row-1][column+1] == opposing )
		{
			sum += (checkCaptureUpRight(x, turnNumber, comp, column+1, row-1));	// there is an opposing player to the upper-right
		}
		if( x[row-1][column] == opposing )
		{
			sum += (checkCaptureUp(x, turnNumber, comp, column, row-1));		// there is an opposing player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column+1] == opposing )
		{
			sum += (checkCaptureDnRight(x, turnNumber, comp, column+1, row+1));	// there is an opposing player to the lower-right
		}
		if( x[row+1][column] == opposing )
		{
			sum += (checkCaptureDown(x, turnNumber, comp, column, row+1));		// there is an opposing player downwards
		}
	}

	return sum;
}

int makeMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)// this function checks for flips with moves in right-most column
{												// and passes along total flips made
	char opposing = getOpposingPlayer(turnNumber);

	int sum = 0;									// this is the sum of flips made by each of the captures made

	if( x[row][column-1] == opposing )
	{
		sum += (checkCaptureLeft(x, turnNumber, comp, column-1, row));			// there is an opposing player to the left
	}

	if( row != 0 )
	{
		if( x[row-1][column-1] == opposing )
		{
			sum += (checkCaptureUpLeft(x, turnNumber, comp, column-1, row-1));	// there is an opposing player to the upper-left
		}
		if( x[row-1][column] == opposing )
		{
			sum += (checkCaptureUp(x, turnNumber, comp, column, row-1));		// there is an opposing player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column-1] == opposing )
		{
			sum += (checkCaptureDnLeft(x, turnNumber, comp, column-1, row+1));	// there is an opposing player to the lower-left
		}
		if( x[row+1][column] == opposing )
		{
			sum += (checkCaptureDown(x, turnNumber, comp, column, row+1));		// there is an opposing player downwards
		}
	}

	return sum;
}

int makeMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function check for flips with moves in the middle of the board
{												// and passes along total flips made
	char opposing = getOpposingPlayer(turnNumber);	

	int sum = 0;									// this is the sum of flips made by each of the captures made

	if( x[row][column-1] == opposing )
	{
		sum += (checkCaptureLeft(x, turnNumber, comp, column-1, row));			// there is an opposing player to the left
	}
	if( x[row][column+1] == opposing )
	{
		sum += (checkCaptureRight(x, turnNumber, comp, column+1, row));			// there is an opposing player to the right
	}
	if( x[row+1][column] == opposing )
	{
		sum += (checkCaptureDown(x, turnNumber, comp, column, row+1));			// there is an opposing player downwards
	}
	if( x[row+1][column-1] == opposing )
	{
		sum += (checkCaptureDnLeft(x, turnNumber, comp, column-1, row+1));		// there is an opposing player to the lower-left
	}
	if( x[row+1][column+1] == opposing )
	{
		sum += (checkCaptureDnRight(x, turnNumber, comp, column+1, row+1));		// there is an opposing player to the lower-right
	}
	if( x[row-1][column] == opposing )
	{
		sum += (checkCaptureUp(x, turnNumber, comp, column, row-1));			// there is an opposing player upwards
	}
	if( x[row-1][column-1] == opposing )
	{
		sum += (checkCaptureUpLeft(x, turnNumber, comp, column-1, row-1));		// there is an opposing player to the upper-left
	}
	if( x[row-1][column+1] == opposing )
	{
		sum += (checkCaptureUpRight(x, turnNumber, comp, column+1, row-1));		// there is an opposing player to the upper-right
	}

	return sum;
}

//

int checkCaptureLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture to the left
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( column == 0 && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row][column-1] == opposing )	
	{
		return (checkCaptureLeft(x, turnNumber, comp, column-1, row));	// continue looking for enemies in line
	}	
	else if( x[row][column-1] == current )	
	{
		return (makeFlipsLeft(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

int checkCaptureUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture to the upper left
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (column == 0 || row == 0) && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row-1][column-1] == opposing )	
	{
		return (checkCaptureUpLeft(x, turnNumber, comp, column-1, row-1));	// continue looking for enemies in line
	}	
	else if( x[row-1][column-1] == current )	
	{
		return (makeFlipsUpLeft(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

int checkCaptureUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)		// this function checks for capture upward
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( row == 0 && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row-1][column] == opposing )	
	{
		return (checkCaptureUp(x, turnNumber, comp, column, row-1));	// continue looking for enemies in line
	}	
	else if( x[row-1][column] == current )	
	{
		return (makeFlipsUp(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

int checkCaptureUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture to the upper right
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (row == 0 || column == (BOARD_SIZE-1)) && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row-1][column+1] == opposing )	
	{
		return (checkCaptureUpRight(x, turnNumber, comp, column+1, row-1));	// continue looking for enemies in line
	}	
	else if( x[row-1][column+1] == current )	
	{
		return (makeFlipsUpRight(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

int checkCaptureRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture to the right
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( column == (BOARD_SIZE-1) && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row][column+1] == opposing )	
	{
		return (checkCaptureRight(x, turnNumber, comp, column+1, row));	// continue looking for enemies in line
	}	
	else if( x[row][column+1] == current )	
	{
		return (makeFlipsRight(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

int checkCaptureDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture to the lower right
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (row == (BOARD_SIZE-1) || column == (BOARD_SIZE-1)) && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row+1][column+1] == opposing )	
	{
		return (checkCaptureDnRight(x, turnNumber, comp, column+1, row+1));	// continue looking for enemies in line
	}	
	else if( x[row+1][column+1] == current )	
	{
		return (makeFlipsDnRight(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)	
}

int checkCaptureDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture downwards
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( row == (BOARD_SIZE-1) && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row+1][column] == opposing )	
	{
		return (checkCaptureDown(x, turnNumber, comp, column, row+1));	// continue looking for enemies in line
	}	
	else if( x[row+1][column] == current )	
	{
		return (makeFlipsDown(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

int checkCaptureDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int comp, int column, int row)	// this function checks for capture to the lower left
{													// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (row == (BOARD_SIZE-1) || column == 0) && x[row][column] != current)				
	{
		return 0;							// we have reached a dead end without capturing
	}
	else if( x[row+1][column-1] == opposing )	
	{
		return (checkCaptureDnLeft(x, turnNumber, comp, column-1, row+1));	// continue looking for enemies in line
	}	
	else if( x[row+1][column-1] == current )	
	{
		return (makeFlipsDnLeft(x, turnNumber, 0, comp, column, row));	// enemy line has ended, time to flip enemies and pass along number of flips
	}

	return 0;								// otherwise return 0 (if the checked position is unoccupied, so no trap)
}

//

int makeFlipsLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)	// this function makes and counts flips to the left
{														// and passes along total flips made
	char current = getPlayer(turnNumber);	
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsLeft(x, turnNumber, previous+1, comp, column+1, row));	// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)// this function makes and counts flips to the upleft
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsUpLeft(x, turnNumber, previous+1, comp, column+1, row+1));	// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)	// this function makes and counts flips upwards
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsUp(x, turnNumber, previous+1, comp, column, row+1));	// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)// this function makes and counts flips to the upright
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsUpRight(x, turnNumber, previous+1, comp, column-1, row+1));	// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)	// this function makes and counts flips to the right
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsRight(x, turnNumber, previous+1, comp, column-1, row));// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)// this function makes and counts flips to the lright
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsDnRight(x, turnNumber, previous+1, comp, column-1, row-1));	// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)	// this function makes and counts flips downward
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsDown(x, turnNumber, previous+1, comp, column, row-1));	// recursively look for more enemies to flip
	}

	return previous;
}

int makeFlipsDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int previous, int comp, int column, int row)// this function makes and counts flips to the lleft
{														// and passes along total flips made
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )							// we will move to the right because the enemies are to the left
	{
		if( comp == 0 ) 	x[row][column] = current;			// only make flips if it is a user choice, computer waits until done analyzing
		return (makeFlipsDnLeft(x, turnNumber, previous+1, comp, column+1, row-1));	// recursively look for more enemies to flip
	}

	return previous;
}

//

void checkWinner(char x[BOARD_SIZE][BOARD_SIZE])
{
	int row;
	int col;

	int xCount = 0;
	int oCount = 0;

	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			if( x[row][col] == 'X' )
			{
				xCount++;
			}
			else if( x[row][col] == 'O' )
			{
				oCount++;
			}
		}
	}	

	if( xCount > oCount )
	{
		printf("Player X has %d soldiers remaining.\n", xCount);
		printf("Player O has %d soldiers remaining.\n", oCount);
		printf("You are the winner!\n\n");
	}
	else if( oCount > xCount )
	{
		printf("Player O has %d soldiers remaining.\n", oCount);
		printf("Player X has %d soldiers remaining.\n", xCount);
		printf("You are the loser!\n\n");
	}
	else
	{
		printf("There is a tie! Each player has %d soldiers remaining!\n\n", xCount);
	}
}

// computer player specific function definitions

void AImove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber)	// this function finds the best move for the computer based on number of flips made and position
{
	int row;	
	int col;

	int current;						// this is the amount of flips for the current position
	int max = 0;						// this is the current maximum amount of flips made by the best move
	
	int rowMax;						// these are the coordinates of the current best move
	int colMax;

	for( row = 0; row < BOARD_SIZE; row++ )				// for every row, evaluate every column
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			if( AIcheckMove(x, turnNumber, col, row) )	// this function evaluates to true only if the computer is considering a valid move
			{
				current = makeMove(x, turnNumber, 1, col, row);
				//printf("row: %d, col: %d, flips: %d\n", row, col, current);
	
				if( current > max )
				{
					max = current;
					rowMax = row;
					colMax = col;
				}
				else if( current == max )
				{
					if( AIrank(x, colMax, rowMax, col, row) == 2 )		// this means that the current position outranks the current maximum
					{	
						rowMax = row;
						colMax = col;
					}					
				}

				x[row][col] = '.';						// we get rid of our changes to the board until the end
			}
		}
	}

	makeMove(x, turnNumber, 0, colMax, rowMax);			// comp boolean is 0 because we want flips to occur now that bext move is determined
	printf("Player O moves: %d %d\n", colMax, rowMax);		// computer's move is displays
	//printf("The best move is row: %d, col: %d, which causes %d flips to occur.\n", rowMax, colMax, max);
}

int AIrank(char x[BOARD_SIZE][BOARD_SIZE], int column1, int row1, int column2, int row2)// this function determines which of two moves (with same flip number) is better
{											// based on the fact that corner spots are the best, followed by edges
	if( (column1 == 0 || column1 == (BOARD_SIZE-1))	&& (row1 == 0 || row1 == (BOARD_SIZE-1)) )
	{
		return 1;					// we give preference to move #1, because it is one of the corners of the board
	}
	else if( (column2 == 0 || column2 == (BOARD_SIZE-1)) && (row2 == 0 || row2 == (BOARD_SIZE-1)) )
	{
		return 2;					// we give preference to move #2, because it is one of the corners of the board
	}
	else if( column1 == 0 || column1 == (BOARD_SIZE-1) || row1 == 0 || row1 == (BOARD_SIZE-1) )
	{
		return 1;					// we give preference to move #1, because it is an edge piece
	}
	else if( column2 == 0 || column2 == (BOARD_SIZE-1) || row2 == 0 || row2 == (BOARD_SIZE-1) )
	{
		return 2;					// we give preference to move #2, because it is an edge piece
	}
	else
	{
		return 1;					// if both pieces are anywhere in the middle, give preference to move #1
	}
}

int AIcheckMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function forces the computer to make a valid move
{
	if( x[row][column] != '.' )							// move must be in unoccupied space
	{
		return 0;
	}

	if( row == 0 )									// now we need to make sure moves are adjacent to other soldiers	
	{
		return (AIcheckMoveTop(x, turnNumber, column, row));			// we know the move is in top row of board
	}
	else if( row == (BOARD_SIZE-1) )
	{
		return (AIcheckMoveBottom(x, turnNumber, column, row));			// we know the move is in bottom row of board
	}
	else if( column == 0 )
	{
		return (AIcheckMoveLeft(x, turnNumber, column, row));			// we know the move is in left-most column of board
	}
	else if( column == (BOARD_SIZE-1) )
	{
		return (AIcheckMoveRight(x, turnNumber, column, row));			// we know the move is in right-most column of board
	}
	else
	{
		return (AIcheckMoveMid(x, turnNumber, column, row));			// we know the move is in the middle of the board
	}
}

int AIcheckMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for adjacency with moves in top row
{
	if( x[row+1][column] != '.' )
	{
		return 1;								// there is a player downwards
	}

	if( column != 0 )
	{
		if( x[row][column-1] != '.' )
		{
			return 1;							// there is a player to the left
		}
		
		if( x[row+1][column-1] != '.' )
		{
			return 1;							// there is a player to the lower-left
		}
	}		

	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] != '.' )
		{
			return 1;							// there is a player to the right
		}
		if( x[row+1][column+1] != '.' )
		{
			return 1;							// there is a player to the lower-right
		}
	}

	return 0;
}

int AIcheckMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for adjacency with moves in bottom row
{
	if( x[row-1][column] != '.' )
	{
		return 1;								// there is a player upward
	}

	if( column != 0 )
	{
		if( x[row][column-1] != '.' )
		{
			return 1;							// there is a player to the left
		}
		if( x[row-1][column-1] != '.' )
		{
			return 1;							// there is a player to the upper-left
		}
	}
	
	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] != '.' )
		{
			return 1;							// there is a player to the right
		}	
		if( x[row-1][column+1] != '.' )
		{
			return 1;							// there is a player to the upper-right
		}
	}

	return 0;
}

int AIcheckMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for adjacency with moves in left-most column 
{
	if( x[row][column+1] != '.' )
	{
		return 1;								// there is a player to the right
	}

	if( row != 0 )
	{
		if( x[row-1][column+1] != '.' )
		{
			return 1;							// there is a player to the upper-right
		}
		if( x[row-1][column] != '.' )
		{
			return 1;							// there is a player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column+1] != '.' )
		{
			return 1;							// there is a player to the lower-right
		}
		if( x[row+1][column] != '.' )
		{
			return 1;							// there is a player downwards
		}
	}

	return 0;
}

int AIcheckMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for adjacency with moves in right-most column
{
	if( x[row][column-1] != '.' )
	{
		return 1;								// there is a player to the left
	}

	if( row != 0 )
	{
		if( x[row-1][column-1] != '.' )
		{
			return 1;							// there is a player to the upper-left
		}
		if( x[row-1][column] != '.' )
		{
			return 1;							// there is a player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column-1] != '.' )
		{
			return 1;							// there is a player to the lower-left
		}
		if( x[row+1][column] != '.' )
		{
			return 1;							// there is a player downwards
		}
	}

	return 0;
}

int AIcheckMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function check for adjacency with moves in the middle of the board
{
	if( x[row][column-1] != '.' )
	{
		return 1;								// there is a player to the left
	}
	if( x[row][column+1] != '.' )
	{
		return 1;								// there is a player to the right
	}
	if( x[row+1][column] != '.' )
	{
		return 1;								// there is a player downwards
	}
	if( x[row+1][column-1] != '.' )
	{
		return 1;								// there is a player to the lower-left
	}
	if( x[row+1][column+1] != '.' )
	{
		return 1;								// there is a player to the lower-right
	}
	if( x[row-1][column] != '.' )
	{
		return 1;								// there is a player upwards
	}
	if( x[row-1][column-1] != '.' )
	{
		return 1;								// there is an opposing player to the upper-left
	}
	if( x[row-1][column+1] != '.' )
	{
		return 1;								// there is an opposing player to the upper-right
	}

	return 0;
}

// begin the main method

int main(void)
{
	char currentBoard[BOARD_SIZE][BOARD_SIZE];

	int turnNumber = 1;

	printf("\nWelcome to Othello!\n\n\tEach player makes their move by specifying the column\n\tand row coordinates, separated by a space. Each new\n\t");
	printf("soldier must be placed adjacent to another. Trap your\n\tenemy between two of your own soldiers to capture\n\ttheir forces. ");
	printf("Capture the most forces to win!\n\n");

        printf("Starting board:\n");

	initializeBoard(currentBoard);
	configureBoard(currentBoard);				// these functions set up the board for a new game

	displayBoard(currentBoard);		
	
	while( checkBoard(currentBoard) )			// continue the game as long as there is one available spot
	{
		if( turnNumber % 2 != 0 )			// odd number turns are the user turns
		{
			getInput(currentBoard, turnNumber);		// get input from the user
			displayBoard(currentBoard);			
		}
		else						// even number turns are the computer turns
		{
			usleep(1000000);				// pause to allow computer to "think"
			AImove(currentBoard, turnNumber);		// get move from the computer
			displayBoard(currentBoard);
		}

		turnNumber++;
	}
		
	checkWinner(currentBoard);				// once the board is full, check for winner
}

