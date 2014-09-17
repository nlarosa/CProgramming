#include <stdio.h>
#include <math.h>

int main(void)		// we will calculate the solar panelling necessary to power a certain number of homes
{
	float efficiency;		// efficiency of solar panels (100% efficiency gives 1000 watts/m^2)
	float hours;			// average hours of sunlight per day
	float houses;			// number of houses being powered (each house uses 14000 watt hours per day)

	float area;			// calculate area of solar paneling needed
	float house_power = 14000;	// (constant) every house consumes 14,000 watt-hours

	printf("Welcome to The Solar Energy Calculator!\n");
	printf("This program calculates the number of solar panelling necessary to power a certain number of homes.\n");
	
	printf("Please enter the percent efficiency of your solar panels (1-100): ");		// receiving efficiency
	if( (scanf("%f",&efficiency) != 1) || (efficiency > 100) || (efficiency < 1) )		// protecting against inappropraite input
	{
		printf("The percent efficiency must be a number between 1 and 100. Please try again!\n");
		return 0;
	}
		
	printf("Please enter the average hours of sunlight available in your area (1-24): ");	// recieving hours			
	if( (scanf("%f",&hours) != 1) || (hours > 24) || (hours < 1) )				// protecting against inappropriate input
	{	
		printf("The hours of sunlight must be a number between 1 and 24. Please try again!\n");
		return 0;
	}
	
	printf("Please enter the number of homes being powered by these solar cells (>1): ");	// recieving houses
	if( (scanf("%f",&houses) != 1) || (houses < 1) )					// protecting against inappropriate input
	{
		printf("The number of homes must be a number greater than 1. Please try again!\n");
		return 0;
	}	

	area = ((house_power)*(houses)) / ((efficiency*10)*(hours));		// main calculation

	printf("In order to power these homes, %f panels measuring 1 square meter each are necessary, or %f panels per home.\n", area, area/houses);
	return 0;
}

