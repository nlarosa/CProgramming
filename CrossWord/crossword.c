// CSE 20211
//
// Lab #8
//
// crossword.c
//
// This program allows the user to enter a list of words
// that are then arranged into a crossword puzzle, with
// anagram and coordinate clues provided
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define BOARD_SIZE 15						// this is a macro for our constant board size (15x15)

void initializeBoard(char board[][BOARD_SIZE])			// this function fills our solution array with all '.'
{
	int row;
	int col;

	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			board[row][col] = '.';
		}
	}
}

void displayBoard(char board[][BOARD_SIZE])			// this function clears the prints a board to the screen
{
        printf("\n");

        int row;						// keep track of rows
        int col;						// keep track of columns

        printf("\n\t   ");

        for( col = 0; col < BOARD_SIZE; col++ )                 // this displays a row of column number labels
        {
                if( col < 10 )  printf(" %d ", col);            // we need to make sure board is aligned
                else            printf("%d ", col);
        }

        printf("\n\n");

        for( row = 0; row < BOARD_SIZE; row++ )			// print all rows in the matrix
        {
                if( row < 10 )  printf("\t%d   ", row);          // we need to make sure board is aligned
                else            printf("\t%d  ", row);

                for( col = 0; col < BOARD_SIZE; col++ )
                {
                        printf("%c  ", board[row][col]);
                }

                printf("\n");
        }

        printf("\n");
}

void convertPuzzle(char board[][BOARD_SIZE], char newBoard[][BOARD_SIZE])	// this function creates a crossword puzzle from the solution puzzle
{										// where '.' becomes 'X' and letters become spaces
	int row;
	int col;
	
	for( row = 0; row < BOARD_SIZE; row++ )
	{
		for( col = 0; col < BOARD_SIZE; col++ )
		{
			if( board[row][col] == '.' )		// all empty spots in solution matrix
			{
				newBoard[row][col] = '#';
			}
			else					// all alphabetic characters
			{
				newBoard[row][col] = ' ';
			}
		}
	}
}

int getInput(char words[][16])					// this function retrieves a series of at most 20 strings, ended by a period
{
	int i = 0;
	int j = 0;
	int quit = 0;						// when to stop recording words
	int error = 0;

	printf("Enter a list of words, ended by '.':\n");

	while(1)
	{
		if( scanf("%s", words[i]) == 1 )		// string of length 15 required
		{
			for( j = 0; j < strlen(words[i]); j++ )
			{
				if( !isalpha(words[i][j]) )	error = 1;	// there is a non-alphabetic character present, throw error
				
				if( words[i][j] == '.' )
				{
					quit = 1;
					error = 0;
				}
			}	
	
			if( strlen(words[i]) > 15 )		error = 1;	// our string needs to be less than 15 characters

			if( error == 1 )
			{
				printf("Please enter a string of only 15 or less alphabetic characters A-Z.\n");
				error = 0;
				i--;
			}
			else if( i >= 20 && quit != 1 )		// we have entered 20 words and not gotten an exit signal
			{
				printf("The maximum number of words allowed is 20. Your list has been truncated to the first 20 words entered.\n");
				break;
			}

			i++;
		}
		else
		{
			printf("Please enter a valid string with a maximum length of 15 characters.\n");
			break;
		}

		if( quit == 1 )	break;
	}

	printf("\n");

	if( i == 1 )						// start over if the user's list contains no words
	{
		printf("Your list must contain one or more words. Please try again.\n\n");
		return 0;
	}
	
	return i-1;						// the number of words entered is the variable i-1 (subtract period)
}

int upperWords(char words[][16])				// this function converts all words to upper case
{
	int size = getInput(words);
	int i;
	int j;

	for( i = 0; i < size; i++ )
	{
		for( j = 0; j < strlen(words[i]); j++ )
		{
			words[i][j] = toupper(words[i][j]);	// capitalize every character
		}
	}
}

int pointWords(char words[][16], const char *pointers[20])	// this function pairs pointers with words
{
	int size = upperWords(words);				// get number of words so we can ignore other word arrays
	int i;

	if( size != 0 )
	{
		for( i = 0; i < size; i++ )
		{
			pointers[i] = words[i];				// point to words
		}
	}

	return size;
}

int sortWords(char words[][16], const char *pointers[])		// this function rearranges the array of pointers so words are pointed to in decending length
{
	int size = pointWords(words, pointers);

	int i;
	int j;
	const char *temp;					// we will be switching pointers, so we need a placeholder

	if( size != 0 )
	{
		for( i = 0; i < size-1; i++ )				// we need to go through bubble sort (size-1) times
		{
			for( j = 0; j < size-i-1; j++ )
			{
				if( strlen(pointers[j]) < strlen(pointers[j+1]) )	// if an element is shorter than the next, switch them
				{
					temp = pointers[j];
					pointers[j] = pointers[j+1];
					pointers[j+1] = temp;
				}
			}
		}
	}

	return size;
}

void placeWord(char board[][BOARD_SIZE], const char word[], int row, int col, char direction)
{						// this function places the given string starting at the given position with specified direction
	int i;

	for( i = 0; i < strlen(word); i++ )
	{
		board[row][col] = word[i];
		
		if( direction == 'v' )		// place word vertically (progressing downward)
		{
			row++;
		}
		else				// place word horizontally (progressing to the right)
		{
			col++;
		}
	}
}

int firstWord(char board[][BOARD_SIZE], char words[][16], const char *pointers[], int clueC[][2], char clueD[])	
{						// this function places the longest word in the middle of the board
	int size = sortWords(words, pointers);

	if( size != 0 )
	{
		int firstLength = strlen(pointers[0]);	// this first word is the longest, we will place it in the middle	

		int row = 7;
		int col = (15-firstLength)/2;		// we need to put word in the middle columns

		placeWord(board, pointers[0], row, col, 'h');
		clueC[0][0] = col;					
		clueC[0][1] = row;						// store the coordinates, direction, and anagrams
		clueD[0] = 'a';			
		strfry(pointers[0]);						// the strfry function creates an anagram out of a string
	}

	return size;
}

int checkPlacementHoriz(char board[][BOARD_SIZE], const char word[], int row, int col)		// returns a boolean if a word can be placed horizontally at position
{
	int i;
	int tempBool = 0;			// temporary true-false value, whether or not word will fit
	int length = strlen(word);

	if( col != 0 && board[row][col-1] != '.' )			return 0;	// there is a character already at the beginning of the string
	else if( board[row][col+length] != '.' )			return 0;	// there is a character that would connect to the end of this word

	for( i = 0; i < length; i++ )
	{
		if( word[i] == board[row][col] && tempBool == 1 )	return 0;	// can't have more than one intersection

		if( board[row][col] != '.' && word[i] != board[row][col] )	return 0;	// the word intersects at an uncommon letter

		if( row >= 15 || col >= 15 )                            return 0;       // can't have string going out of the array

		if( row == 0 )
		{
			if( board[row+1][col] != '.' )
			{
				if( word[i] == board[row][col] )	tempBool = 1;	// this is a clean intersection		
				else					return 0;	// this position is surrounded by other words
			}
		}
		else if( row == 14 )
		{
			if( board[row-1][col] != '.' )
			{
				if( word[i] == board[row][col] )	tempBool = 1;	// this is a clean intersection		
				else					return 0;	// this position is surrounded by other words
			}
		}
		else
		{
			if( board[row+1][col] != '.' || board[row-1][col] != '.' )	
			{
				if( word[i] == board[row][col] )	tempBool = 1;	// this is a clean intersection
				else					return 0;	// this position is surrounded by other words
			}	
		}

		if( word[i] == board[row][col] && tempBool != 1 )	tempBool = 1;	// check for the first intersection
	
		col++;
	}

	if( tempBool == 1 )						return 1;	// one intersection surrounded by no adjacent words
	else								return 0;	// there were no intersections
}

int checkPlacementVert(char board[][BOARD_SIZE], const char word[], int row, int col)		// returns a boolean if a word can be placed vertically at position
{
	int i;
	int tempBool = 0;			// temporary true-false value, whether or not word will fit
	int length = strlen(word);

	if( row != 0 && board[row-1][col] != '.' )			return 0;	// there is a character already at the beginning of the string
	else if( board[row+length][col] != '.' )			return 0;	// there is a character that would connect to the end of this word

	for( i = 0; i < length; i++ )
	{
		if( word[i] == board[row][col] && tempBool == 1 )	return 0;	// can't have more than one intersection

		if( board[row][col] != '.' && word[i] != board[row][col] )	return 0;	// the word intersects at an uncommon letter

		if( row >= 15 || col >= 15 )                            return 0;       // can't have string going out of the array

		if( col == 0 )
		{
			if( board[row][col+1] != '.' )
			{
				if( word[i] == board[row][col] )	tempBool = 1;	// this is a clean intersection		
				else					return 0;	// this position is surrounded by other words
			}
		}
		if( col == 14 )
		{
			if( board[row][col-1] != '.' )
			{
				if( word[i] == board[row][col] )	tempBool = 1;	// this is a clean intersection		
				else					return 0;	// this position is surrounded by other words
			}
		}
		else
		{
			if( board[row][col-1] != '.' || board[row][col+1] != '.' )	
			{
				if( word[i] == board[row][col] )	tempBool = 1;	// this is a clean intersection
				else					return 0;	// this position is surrounded by other words
			}	
		}

		if( word[i] == board[row][col] && tempBool != 1 )	tempBool = 1;	// check for the first intersection
	
		row++;
	}

	if( tempBool == 1 )						return 1;	// one intersection surrounded by no adjacent words
	else								return 0;	// there were no intersections
}

int configureWords(char board[][BOARD_SIZE], char words[][16], const char *pointers[], int clueC[][2], char clueD[], int needClues[])	
{						// this function places all words on the board and stores clues in respective arrays
	int size = firstWord(board, words, pointers, clueC, clueD);
	int i;
	int row;
	int col;

	int foundSpot;				// boolean to stop after finding first spot for word

	if( size != 0 )
	{
		for( i = 1; i < size; i++ )					// for every word besides the first (already placed)...
		{
			foundSpot = 0;

			for( row = 0; row < 15; row++ )				// check if it can be placed at every position on the board
			{							// stopping after finding the first spot for the word
				if( foundSpot )			break;

				for( col = 0; col < 15; col++ )	
				{
					if( foundSpot )		break;

					if( checkPlacementHoriz(board, pointers[i], row, col) )			// first try to the find a horizontal placement
					{
						placeWord(board, pointers[i], row, col, 'h');			// place the word horizontally
						clueC[i][0] = col;					
						clueC[i][1] = row;						// store the coordinates, direction, and anagrams
						clueD[i] = 'a';						
						strfry(pointers[i]);						// the strfry function creates an anagram out of a string
						needClues[i] = 1;
						foundSpot = 1;
					}

					if( checkPlacementVert(board, pointers[i], row, col) && !foundSpot )	// only try to place vertically if no horizontal placement
					{
						placeWord(board, pointers[i], row, col, 'v');			// place word vertically
						clueC[i][0] = col;					
						clueC[i][1] = row;						// store the coordinates, direction, and anagrams
						clueD[i] = 'd';					
						strfry(pointers[i]);						// the strfry function creates an anagram out of a string
						needClues[i] = 1;
						foundSpot = 1;
					}
				}	
			}

			if( !foundSpot )
			{
				printf("The following word could not be placed legally: %s\n", pointers[i]);	// notify user if word cannot be placed
				needClues[i] = 0;
			}
		}

		printf("\n");
	}

	return size;
}

void printClues(int clueC[][2], char clueD[], const char *pointers[], int needClues[], int size)	
{											// this function will print our clue arrays in the correct format
	int i;

	for( i = 0; i < size; i++ )
	{
		if( needClues[i] )			// only print clues if the word was placed in the puzzle
		{
			printf("\t");
		
			if( clueC[i][0] >= 10 )		printf("%d", clueC[i][0]);		// print column number
			else				printf(" %d", clueC[i][0]);

			printf(",");	

			if( clueC[i][1] >= 10 )		printf("%d", clueC[i][1]);		// print row number
			else				printf(" %d", clueC[i][1]);
	
			printf("\t");

			if( clueD[i] == 'a' )	printf("%s\t", "Across");			// print direction
			else			printf("%s\t", "Down");				

			printf("%s", pointers[i]);						// print anagram
		
			printf("\n");
		}
	}
}

void playCrossword(char board[][BOARD_SIZE], char nextBoard[][BOARD_SIZE], char words[][16], const char *pointers[], int clueC[][2], char clueD[], int needClues[])
{								// this function runs all correct functions in sequence to create complete game
	int size;						// keep track of the number of words entered	

	initializeBoard(board);
	
	printf("\n\t");
	printf("Anagram Crossword Puzzle Generator\n");
	printf("\t");
	printf("__________________________________\n");
	printf("\n\t");
	printf("    Created by Nicholas LaRosa    \n");
	printf("\n");

	size = configureWords(board, words, pointers, clueC, clueD, needClues);

	if( size != 0 )
	{
		printf("Solution:");

		displayBoard(board);

		printf("Crossword Puzzle:");

		convertPuzzle(board, nextBoard);

		displayBoard(nextBoard);

		printf("Clues:\n\n");

		printClues(clueC, clueD, pointers, needClues, size);

		printf("\n");
	}
}

void main()
{
	char solutionBoard[BOARD_SIZE][BOARD_SIZE];		// this holds the solution board
	char puzzleBoard[BOARD_SIZE][BOARD_SIZE];		// this holds the actual puzzle board
	char wordArray[20][16];					// maximum 20 words of length 15
	const char *words[20];					// array of 20 pointers to sort word list	

	int clueCoordinates[20][2];				// contains row and column coordinates of each word
	char clueDirections[20];				// contains the directions of each word placed on board

	int needClues[20];					// contains the indeces of words that were placed in the puzzle

	playCrossword(solutionBoard, puzzleBoard, wordArray, words, clueCoordinates, clueDirections, needClues);
}

