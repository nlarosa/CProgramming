#include <stdio.h>

int main(void)				// our main method
{
	int touchdowns;			// create all our variables
	int extraPoints;
	int fieldGoals;
	int safeties;

	int score;			// final placeholder for our total score
		
	printf("Welcome to the Irish Football Score Calculator!\n");
	
	printf("Enter the number of touchdowns scored by the Irish: ");		// ask the user for touchdowns
	scanf("%d",&touchdowns);

	printf("Enter the number of extra points scored by the Irish: ");	// ask the user for extra points
	scanf("%d",&extraPoints);
		
	printf("Enter the number of field goals scored by the Irish: ");	// ask the user for field goals
	scanf("%d",&fieldGoals);

	printf("Enter the number of safeties scored by the Irish: ");		// ask the user for safeties
	scanf("%d",&safeties);

	score = (6*touchdowns) + (extraPoints) + (3*fieldGoals) + (2*safeties);	// we have all the variables, make calculation

	printf("The Fighting Irish scored %d points total!\n", score);		// print our final results

	return 0;			// return statement
}

