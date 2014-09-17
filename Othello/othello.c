// CSE 20211
//
// othello.c
//
// This program allows for two players to play the game Othello.
// The two players must place "soldiers" on a board, trying to trap 
// enemy "soldiers" between their own. Further instructions are 
// available upon loading the game.
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BOARD_SIZE 8		// this is a macro for our board size

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

void makeMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);		// prototypes for determining surrounding enemies
void makeMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);

void checkCaptureLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);	// prototypes for finding groups of enemies
void checkCaptureUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkCaptureUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkCaptureUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkCaptureRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkCaptureDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkCaptureDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void checkCaptureDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);

void makeFlipsLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);	// prototypes for making the actual flips once group found
void makeFlipsUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeFlipsUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeFlipsUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeFlipsRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeFlipsDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeFlipsDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);
void makeFlipsDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row);

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
		makeMove(x, turnNumber, column, row);
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
		makeMove(x, turnNumber, column, row);
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
		makeMove(x, turnNumber, column, row);
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
		makeMove(x, turnNumber, column, row);
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
		makeMove(x, turnNumber, column, row);
	}
	else
	{
		printf("Your soldier must be placed adjacent to another.\n");
		getInput(x, turnNumber);
	}
}

void makeMove(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function makes changes to the game board and checks position
{
	char current = getPlayer(turnNumber);
	
	x[row][column] = current;

	if( row == 0 )
	{
		makeMoveTop(x, turnNumber, column, row);				// we know the move is in top row of board
	}
	else if( row == (BOARD_SIZE-1) )
	{
		makeMoveBottom(x, turnNumber, column, row);				// we know the move is in bottom row of board
	}
	else if( column == 0 )
	{
		makeMoveLeft(x, turnNumber, column, row);				// we know the move is in left-most column of board
	}
	else if( column == (BOARD_SIZE-1) )
	{
		makeMoveRight(x, turnNumber, column, row);				// we know the move is in right-most column of board
	}
	else
	{
		makeMoveMid(x, turnNumber, column, row);				// we know the move is in the middle of the board
	}
}

void makeMoveTop(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for flips with moves in top row
{
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row+1][column] == opposing )
	{
		checkCaptureDown(x, turnNumber, column, row+1);				// there is an opposing player downward
	}

	if( column != 0 )
	{
		if( x[row][column-1] == opposing )
		{
			checkCaptureLeft(x, turnNumber, column-1, row);			// there is an opposing player to the left
		}
		
		if( x[row+1][column-1] == opposing )
		{
			checkCaptureDnLeft(x, turnNumber, column-1, row+1);		// there is an opposing player to the lower-left
		}
	}		

	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] == opposing )
		{
			checkCaptureRight(x, turnNumber, column+1, row);		// there is an opposing player to the right
		}
		if( x[row+1][column+1] == opposing )
		{
			checkCaptureDnRight(x, turnNumber, column+1, row+1);		// there is an opposing player to the lower-right
		}
	}
}

void makeMoveBottom(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)// this function checks for flips with moves in bottom row
{
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row-1][column] == opposing )
	{
		checkCaptureUp(x, turnNumber, column, row-1);				// there is an opposing player upward
	}

	if( column != 0 )
	{
		if( x[row][column-1] == opposing )
		{
			checkCaptureLeft(x, turnNumber, column-1, row);			// there is an opposing player to the left
		}
		if( x[row-1][column-1] == opposing )
		{
			checkCaptureUpLeft(x, turnNumber, column-1, row-1);		// there is an opposing player to the upper-left
		}
	}
	
	if( column != (BOARD_SIZE-1) )
	{
		if( x[row][column+1] == opposing )
		{
			checkCaptureRight(x, turnNumber, column+1, row);		// there is an opposing player to the right
		}	
		if( x[row-1][column+1] == opposing )
		{
			checkCaptureUpRight(x, turnNumber, column+1, row-1);		// there is an opposing player to the upper-right
		}
	}
}

void makeMoveLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for flips with moves in left-most column 
{
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column+1] == opposing )
	{
		checkCaptureRight(x, turnNumber, column+1, row);			// there is an opposing player to the right
	}

	if( row != 0 )
	{
		if( x[row-1][column+1] == opposing )
		{
			checkCaptureUpRight(x, turnNumber, column+1, row-1);		// there is an opposing player to the upper-right
		}
		if( x[row-1][column] == opposing )
		{
			checkCaptureUp(x, turnNumber, column, row-1);			// there is an opposing player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column+1] == opposing )
		{
			checkCaptureDnRight(x, turnNumber, column+1, row+1);		// there is an opposing player to the lower-right
		}
		if( x[row+1][column] == opposing )
		{
			checkCaptureDown(x, turnNumber, column, row+1);			// there is an opposing player downwards
		}
	}
}

void makeMoveRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function checks for flips with moves in right-most column
{
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column-1] == opposing )
	{
		checkCaptureLeft(x, turnNumber, column-1, row);				// there is an opposing player to the left
	}

	if( row != 0 )
	{
		if( x[row-1][column-1] == opposing )
		{
			checkCaptureUpLeft(x, turnNumber, column-1, row-1);		// there is an opposing player to the upper-left
		}
		if( x[row-1][column] == opposing )
		{
			checkCaptureUp(x, turnNumber, column, row-1);			// there is an opposing player upwards
		}
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][column-1] == opposing )
		{
			checkCaptureDnLeft(x, turnNumber, column-1, row+1);		// there is an opposing player to the lower-left
		}
		if( x[row+1][column] == opposing )
		{
			checkCaptureDown(x, turnNumber, column, row+1);			// there is an opposing player downwards
		}
	}
}

void makeMoveMid(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)	// this function check for flips with moves in the middle of the board
{
	char opposing = getOpposingPlayer(turnNumber);	

	if( x[row][column-1] == opposing )
	{
		checkCaptureLeft(x, turnNumber, column-1, row);				// there is an opposing player to the left
	}
	if( x[row][column+1] == opposing )
	{
		checkCaptureRight(x, turnNumber, column+1, row);			// there is an opposing player to the right
	}
	if( x[row+1][column] == opposing )
	{
		checkCaptureDown(x, turnNumber, column, row+1);				// there is an opposing player downwards
	}
	if( x[row+1][column-1] == opposing )
	{
		checkCaptureDnLeft(x, turnNumber, column-1, row+1);			// there is an opposing player to the lower-left
	}
	if( x[row+1][column+1] == opposing )
	{
		checkCaptureDnRight(x, turnNumber, column+1, row+1);			// there is an opposing player to the lower-right
	}
	if( x[row-1][column] == opposing )
	{
		checkCaptureUp(x, turnNumber, column, row-1);				// there is an opposing player upwards
	}
	if( x[row-1][column-1] == opposing )
	{
		checkCaptureUpLeft(x, turnNumber, column-1, row-1);			// there is an opposing player to the upper-left
	}
	if( x[row-1][column+1] == opposing )
	{
		checkCaptureUpRight(x, turnNumber, column+1, row-1);			// there is an opposing player to the upper-right
	}
}

void checkCaptureLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture to the left
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( column == 0 && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row][column-1] == opposing )	
	{
		checkCaptureLeft(x, turnNumber, column-1, row);			// continue looking for enemies in line
	}	
	else if( x[row][column-1] == current )	
	{
		makeFlipsLeft(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture to the upper left
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (column == 0 || row == 0) && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row-1][column-1] == opposing )	
	{
		checkCaptureUpLeft(x, turnNumber, column-1, row-1);		// continue looking for enemies in line
	}	
	else if( x[row-1][column-1] == current )	
	{
		makeFlipsUpLeft(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture upward
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( row == 0 && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row-1][column] == opposing )	
	{
		checkCaptureUp(x, turnNumber, column, row-1);			// continue looking for enemies in line
	}	
	else if( x[row-1][column] == current )	
	{
		makeFlipsUp(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture to the upper right
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (row == 0 || column == (BOARD_SIZE-1)) && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row-1][column+1] == opposing )	
	{
		checkCaptureUpRight(x, turnNumber, column+1, row-1);		// continue looking for enemies in line
	}	
	else if( x[row-1][column+1] == current )	
	{
		makeFlipsUpRight(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture to the right
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( column == (BOARD_SIZE-1) && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row][column+1] == opposing )	
	{
		checkCaptureRight(x, turnNumber, column+1, row);		// continue looking for enemies in line
	}	
	else if( x[row][column+1] == current )	
	{
		makeFlipsRight(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture to the lower right
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (row == (BOARD_SIZE-1) || column == (BOARD_SIZE-1)) && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row+1][column+1] == opposing )	
	{
		checkCaptureDnRight(x, turnNumber, column+1, row+1);		// continue looking for enemies in line
	}	
	else if( x[row+1][column+1] == current )	
	{
		makeFlipsDnRight(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture downwards
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( row == (BOARD_SIZE-1) && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row+1][column] == opposing )	
	{
		checkCaptureDown(x, turnNumber, column, row+1);			// continue looking for enemies in line
	}	
	else if( x[row+1][column] == current )	
	{
		makeFlipsDown(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;
}

void checkCaptureDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function checks for capture to the lower left
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( (row == (BOARD_SIZE-1) || column == 0) && x[row][column] != current)				
	{
		return;								// we have reached a dead end without capturing
	}
	else if( x[row+1][column-1] == opposing )	
	{
		checkCaptureDnLeft(x, turnNumber, column-1, row+1);		// continue looking for enemies in line
	}	
	else if( x[row+1][column-1] == current )	
	{
		makeFlipsDnLeft(x, turnNumber, column, row);			// enemy line has ended, time to flip enemies
	}

	return;	
}

void makeFlipsLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)			// this function actually makes flips to the left
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsLeft(x, turnNumber, column+1, row);			// recursively look for more enemies to flip
	}
}

void makeFlipsUpLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function makes flips to the upper left
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsUpLeft(x, turnNumber, column+1, row+1);		// recursively look for more enemies to flip
	}
}

void makeFlipsUp(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)			// this function makes flips upwards
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsUp(x, turnNumber, column, row+1);			// recursively look for more enemies to flip
	}
}

void makeFlipsUpRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function makes flips to the upper right
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsUpRight(x, turnNumber, column-1, row+1);		// recursively look for more enemies to flip
	}
}

void makeFlipsRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function makes flips to the right
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsRight(x, turnNumber, column-1, row);			// recursively look for more enemies to flip
	}
}

void makeFlipsDnRight(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function makes flips to the lower right
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsDnRight(x, turnNumber, column-1, row-1);		// recursively look for more enemies to flip
	}
}

void makeFlipsDown(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)			// this function makes flips downward
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsDown(x, turnNumber, column, row-1);			// recursively look for more enemies to flip
	}
}

void makeFlipsDnLeft(char x[BOARD_SIZE][BOARD_SIZE], int turnNumber, int column, int row)		// this function makes flips to the lower left
{
	char current = getPlayer(turnNumber);
	char opposing = getOpposingPlayer(turnNumber);

	if( x[row][column] != current )						// we will move to the right because the enemies are to the left
	{
		x[row][column] = current;
		makeFlipsDnLeft(x, turnNumber, column+1, row-1);		// recursively look for more enemies to flip
	}
}

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
		printf("Player X wins with %d soldiers remaining!\n\n", xCount);
	}
	else if( oCount > xCount )
	{
		printf("Player O wins with %d soldiers remaining!\n\n", oCount);
	}
	else
	{
		printf("There is a tie! Each player has %d soldiers remaining!\n\n", xCount);
	}
}

int main(void)
{
	char currentBoard[BOARD_SIZE][BOARD_SIZE];

	int turnNumber = 1;

	printf("\nWelcome to Othello!\n\n\tEach player makes their move by specifying the column\n\tand row coordinates, separated by a space. Each new\n\t");
	printf("soldier must be placed adjacent to another. Trap your\n\tenemy between two of your own soldiers to capture\n\ttheir forces. ");
	printf("Capture the most forces to win!\n\n");

        printf("Starting board:\n");

	initializeBoard(currentBoard);
	configureBoard(currentBoard);

	displayBoard(currentBoard);
	
	while( checkBoard(currentBoard) )
	{
		getInput(currentBoard, turnNumber);
		displayBoard(currentBoard);

		turnNumber++;
	}
		
	checkWinner(currentBoard);
}

