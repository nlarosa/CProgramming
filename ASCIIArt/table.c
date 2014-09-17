#include <stdio.h>

int main(void)		// we will create a multiplication table using two user integer inputs
{
	int topInt;	// along columns
	int sideInt;	// along rows

	int printInt;	// integer being printed

	int t;		// counter for topInt (along columns)
	int s;		// counter for sideInt (along rows)

	printf("\nWelcome to the Integer Multiplication Table Generator!\n");
	
	printf("Please enter the number of columns: ");					// recieve first integer
	if( scanf("%d",&topInt) != 1 )							// check for digit entry
	{
		printf("Your entry must be an integer. Please try again!\n");
		return 0;
	}

	printf("Please enter the number of rows: ");					// recieve second integer
	if( scanf("%d",&sideInt) != 1 )							// check for digit entry
	{
		printf("Your entry must be an integer. Please try again!\n");
		return 0;
	}

	printf("\n");				// formatting

	while( t <= topInt )			// the first row is made up of an incremented topInt
	{
		if( t == 0 )
		{
			printf("   *");		// beginning with an asterisk (4 characters reserved)
			t++;
		}
		
		printf("%4d", t);
		t++;				// increment every column
	}

	printf("\n");
	s = 1;
	t = 1;					// we will be starting from the second row

	while( s <= sideInt )			// we will print the table left to right (one row at a time)
	{
		printInt = s;
		printf("%4d", printInt);	// the first entry in each row is the incremented sideInt

		while( t <= topInt ) 		// for every row (side integer), we will print all the columns (the top integers)
		{
			printInt = s * t;	// we are multiplying every integer in the row by the integers in the top row (topInt)
			
			printf("%4d", printInt);

			t++;			// increment every column
		}
		
		printf("\n");			// create a new row in the table
		s++;				// increment sideInt and reset topInt
		t = 1;
	}
		
	printf("\n");				// formatting

	return 0;
}

