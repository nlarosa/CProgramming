// CSE 20211
//
// We will use the simple rules where a dead cell with 3 neighbors becomes live, 
// and only a live cell with 2 or 3 neighbors survives, all others die. 
//
// If the user enters a, then ask for coordinates where to add a new live cell. (No action is needed if it is already alive.)
// If the user enters r, then ask for coordinates where a cell should be removed. (No action is needed if it is already dead.)
// If the user enters n, then advance the simulation to the next "tick" by applying the rules of the game.
// If the user enters q, then quit the program.
// If the user enters p, then play the game forever without asking for more input. (You can press control-C to stop the program.) 
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 40			// macro for board size

int quit = 0;				// this global variable keeps track of when the game should be ended

// Function prototypes

void initializeBoards(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);		// these functions prepare the boards for the game
void displayBoard(char x[BOARD_SIZE][BOARD_SIZE]);

void getInput(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);			// these functions get input and feed into correct command
void checkInput(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE], char command);

void addCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);			// these functions make up response to 'a'
void addCell(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE], int row, int col);

void removeCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);			// these functions make up response to 'r'
void removeCell(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE], int row, int col);

void tickCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);			// these functions make up response to 'n' and 'p'
void playCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);
void applyRules(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);
void copyBoards(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE]);

int checkLife(char x[BOARD_SIZE][BOARD_SIZE], int row, int col);					// these functions allow us to count surrounding life
int checkLifeTop(char x[BOARD_SIZE][BOARD_SIZE], int row, int col);
int checkLifeBottom(char x[BOARD_SIZE][BOARD_SIZE], int row, int col);
int checkLifeLeft(char x[BOARD_SIZE][BOARD_SIZE], int row, int col);
int checkLifeRight(char x[BOARD_SIZE][BOARD_SIZE], int row, int col);
int checkLifeMid(char x[BOARD_SIZE][BOARD_SIZE], int row, int col);

// Function definitions

void initializeBoards(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	// this function initializes two multi-dimensional arrays to contain all spaces
{
	int row;						// keep track of rows
	int col;						// keep track of columns

	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			x1[row][col] = ' ';			// arrays begin as a blank 40x40 space
			x2[row][col] = ' ';
		}
	}
}

void displayBoard(char x[BOARD_SIZE][BOARD_SIZE])		// this function clears the screen and prints the specified array to the screen
{
	printf("\033[2J\033[H");				// clears the screen
	printf("\n");

	int row;						// keep track of rows
	int col;						// keep track of columns

	printf("\t  ");

	for( col = 0; col < BOARD_SIZE; col++ )			// this displays a row of column number labels
	{
		if( col < 10 )	printf("%d  ", col);		// we need to make sure board is aligned
		else		printf("%d ", col);
	}

	printf("\n");

	for( row = 0; row < BOARD_SIZE; row++ )
	{
		if( row < 10 )	printf("\t%d  ", row);		// we need to make sure board is aligned 
		else		printf("\t%d ", row);

		for( col = 0; col < BOARD_SIZE; col++ )
		{
			printf("%c  ", x[row][col]);
		}
	
		printf("\n");
	}

	printf("\n");
}

void getInput(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	// this function retrieves any input the user enters and checks for errors
{										// because this function is the parent, we need to pass both arrays to it
	char command;

        if( scanf("%c", &command) != 1 )
        {
                while( getchar() != '\n' ) continue;		// clears buffer of wrong input
                displayBoard(x1);				// clears the screen and displays board
		printf("Command not found.\n");
        }
        else
        {
                checkInput(x1, x2, command);
        }
}

void checkInput(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE], char command)	// this function will make sure the user 
{												// enters one of the actual commands (if character entered)
	switch( command )									// if not, nothing happens
	{
		case 'a':
		{
			addCommand(x1, x2);				// this function needs both the current and temporary boards
			break;
		}
		case 'r':
		{
			removeCommand(x1, x2);				// this function needs both the current and temporary boards
			break;
		}
		case 'n':
		{
			tickCommand(x1, x2);				// this function needs both the current and temporary boards
			break;
		}
		case 'q':
		{
			quit = 1;					// it is time to quit the game
			printf("\033[2J\033[H");			// clears the screen
			break;
		}
		case 'p':
		{
			playCommand(x1, x2);				// this function needs both the current and temporary boards
			break;
		}
	}
}

void addCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	
{									// this function executes when 'a' is pressed, allowing user to enter coordinates of new life	
	int row;
	int col;

	displayBoard(x1);						// clears the screen and places the new board
	
	printf("Enter column and row numbers, separated by space: ");	// user must enter: col# row#
	
	if( scanf("%d %d", &col, &row) != 2 )				// if we get incorrect input, retry
	{
		addCommand(x1, x2);					// incorrect input, try again
	}
	else if( col < 0 || col >= BOARD_SIZE || row < 0 || row >= BOARD_SIZE )	// make sure the coordinates are existent
	{
		addCommand(x1, x2);
	}
	else
	{
		addCell(x1, x2, row, col);				// give life to this position
	}
}

void addCell(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE], int row, int col)		
{									// this function will add a cell 'X' to the specified board (current)
	x1[row][col] = 'X';
	x2[row][col] = 'X';
	displayBoard(x1);						// display modified board
}

void removeCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	
{									// this function executes when 'r' is pressed, allows user to enter coordinates to remove life	
	int row;
        int col;

        displayBoard(x1); 						// clears the screen and places the new board

        printf("Enter column and row number, separated by space: ");	// user must enter: col# row#

        if( scanf("%d %d", &col, &row) != 2 )                           // if we get incorrect input, retry
        {
                removeCommand(x1, x2);					// incorrect input, try again
        }
	else if( col < 0 || col >= BOARD_SIZE || row < 0 || row >= BOARD_SIZE )	// make sure the coordinates are existent
	{
		removeCommand(x1, x2);
	}
        else
        {
                removeCell(x1, x2, row, col);				// remove life at this position
        }
}

void removeCell(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE],  int row, int col)	
{									// this function will remove the cell at the specified position in the current board
	x2[row][col] = ' ';						// dead cell is a blank space
	x2[row][col] = ' ';
	displayBoard(x1);						// display modified board
}

void tickCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	// this function executes when 'n' is pressed, advances one rule application
{
	applyRules(x1, x2);						
	copyBoards(x1, x2);						// make sure x1 and x2 are both the modified boards
	displayBoard(x1);						// display the new current board
}

void playCommand(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	// this function executes when p is pressed, 
{
	while(1)
	{	
		tickCommand(x1, x2);					// by calling the tick command in an infinite loop, motion will be continuous
		usleep(330000);						// add a pause for smooth animation
	}
}

void applyRules(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	// this function applies the rules of the game of life to board x1
{
	int row;
	int col;

	int lifeCount;

	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			lifeCount = checkLife(x1, row, col);	// we are checking the cells of x1 (current)  and actually modifying x2

			if( x1[row][col] == 'X' )		// we have a live cell, check to make sure it has two or three live neighbors, otherwise kill it
			{
				if( lifeCount != 2 && lifeCount != 3 )
				{
					x2[row][col] = ' ';	// if has neither two or three neighbors, kill the cell
				}
			}
			else					// we have a dead cell, check to see if it has three neighbors, if it does give it life
			{
				if( lifeCount == 3 )
				{
					x2[row][col] = 'X';	// if three live neighbors, give life, otherwise keep dead
				}
			}
		}
	}
}

void copyBoards(char x1[BOARD_SIZE][BOARD_SIZE], char x2[BOARD_SIZE][BOARD_SIZE])	// this function copies the contents of board x2 to x1
{
	int row;
	int col;
	
	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			x1[row][col] = x2[row][col];					// copy x2 to x1
		}
	}
}

int checkLife(char x[BOARD_SIZE][BOARD_SIZE], int row, int col)				// this function returns the life surrounding a certain position
{
	if( row == 0 )
	{
		return checkLifeTop(x, row, col);					// we know the position is in top row of board
	}
	else if( row == (BOARD_SIZE-1) )
	{
		return checkLifeBottom(x, row, col);					// we know the position is in bottom row of board
	}
	else if( col == 0 )
	{
		return checkLifeLeft(x, row, col);					// we know the position is in left-most column of board
	}
	else if( col == (BOARD_SIZE-1) )
	{
		return checkLifeRight(x, row, col);					// we know the position is in right-most column of board
	}
	else
	{
		return checkLifeMid(x, row, col);					// we know the position is in the middle of the board
	}
}

int checkLifeTop(char x[BOARD_SIZE][BOARD_SIZE], int row, int col)			// this function checks for life with positions in top row
{
	int lifeCount = 0;								// keep track of number of surrounding live cells

	if( x[row+1][col] == 'X' )	lifeCount++;					// there is life downward

	if( col != 0 )
	{
		if( x[row][col-1] == 'X' )	lifeCount++;				// there is life to the left
		
		if( x[row+1][col-1] == 'X' )	lifeCount++;				// there is life to the lower-left
	}		

	if( col != (BOARD_SIZE-1) )
	{
		if( x[row][col+1] == 'X' )	lifeCount++;				// there is life to the right

		if( x[row+1][col+1] == 'X' )	lifeCount++;				// there is life to the lower-right
	}

	return lifeCount;
}

int checkLifeBottom(char x[BOARD_SIZE][BOARD_SIZE], int row, int col)			// this function checks for life with positions in bottom row
{
	int lifeCount = 0;								// keep track of number of surrounding live cells
	
	if( x[row-1][col] == 'X' )	lifeCount++;					// there is life upward

	if( col != 0 )
	{
		if( x[row][col-1] == 'X' )	lifeCount++;				// there is life to the left

		if( x[row-1][col-1] == 'X' )	lifeCount++;				// there is life to the upper-left
	}
	
	if( col != (BOARD_SIZE-1) )
	{
		if( x[row][col+1] == 'X' )	lifeCount++;				// there is life to the right

		if( x[row-1][col+1] == 'X' )	lifeCount++;				// there is life to the upper-right
	}

	return lifeCount;
}

int checkLifeLeft(char x[BOARD_SIZE][BOARD_SIZE], int row, int col)			// this function checks for life with positions in left-most column 
{
	int lifeCount = 0;								// keep track of number of surrounding live cells
	
	if( x[row][col+1] == 'X' )	lifeCount++;					// there is life to the right

	if( row != 0 )
	{
		if( x[row-1][col+1] == 'X' )	lifeCount++;				// there is life to the upper-right

		if( x[row-1][col] == 'X' )	lifeCount++;				// there is life upwards
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][col+1] == 'X' )	lifeCount++;				// there is life to the lower-right
		
		if( x[row+1][col] == 'X' )	lifeCount++;				// there is life downwards
	}

	return lifeCount;
}

int checkLifeRight(char x[BOARD_SIZE][BOARD_SIZE], int row, int col)			// this function checks for life with positions in right-most column
{
	int lifeCount = 0;								// keep track of number of surrounding live cells
	
	if( x[row][col-1] == 'X' )	lifeCount++; 					// there is life to the left

	if( row != 0 )
	{
		if( x[row-1][col-1] == 'X' )	lifeCount++;				// there is life to the upper-left
		
		if( x[row-1][col] == 'X' )	lifeCount++;				// there is life upwards
		
	}
	
	if( row != (BOARD_SIZE-1) )
	{
		if( x[row+1][col-1] == 'X' )	lifeCount++;				// there is life to the lower-left
		
		if( x[row+1][col] == 'X' )	lifeCount++;				// there is life downwards
	}

	return lifeCount;
}

int checkLifeMid(char x[BOARD_SIZE][BOARD_SIZE], int row, int col)			// this function check for life with positions in the middle of the board
{
	int lifeCount = 0;								// keep track of number of surrounding live cells
	
	if( x[row][col-1] == 'X' )	lifeCount++;					// there is life to the left
	
	if( x[row][col+1] == 'X' )	lifeCount++;					// there is life to the right
	
	if( x[row+1][col] == 'X' )	lifeCount++;					// there is life downwards
	
	if( x[row+1][col-1] == 'X' )	lifeCount++;					// there is life to the lower-left
	
	if( x[row+1][col+1] == 'X' )	lifeCount++;					// there is life to the lower-right
	
	if( x[row-1][col] == 'X' )	lifeCount++;					// there is life upwards
	
	if( x[row-1][col-1] == 'X' )	lifeCount++;					// there is life to the upper-left
	
	if( x[row-1][col+1] == 'X' )	lifeCount++;					// there is life to the upper-right

	return lifeCount;
}

int main(void)
{
	char currentBoard[BOARD_SIZE][BOARD_SIZE];		// this is the current board
	char nextBoard[BOARD_SIZE][BOARD_SIZE];			// this will be the next board with rules applied

	initializeBoards(currentBoard, nextBoard);
	displayBoard(currentBoard);

	while( quit != 1 )					// our quit boolean will determine when the game can be played
	{
		getInput(currentBoard, nextBoard);		// gets user input and calls necessary functions depending on the command
	}
}


