#include <stdio.h>

int main(void)			// we will generate an amortization table for every month until the mortgage is paid off
{
	float principle;	// the initial amount of loan money given by the bank
	float interest;		// the YEARLY interest rate on the loan
	float payment;		// the monthly payment by the consumer
	
	float intCharge;	// the monthly interest charged by the bank
	float cutoffPrinc;	// the principle that can be paid off with less than one monthly payment	

	float countTotal = 0;	// keep track of the total money being paid
	int countMonth = 1;	// keep track of the total months 

	printf("\nWelcome to The Amortization Table Generator!\n");
	
	printf("\nPlease enter the inital amount loaned to you by the bank (principle, in dollars): ");
	if( (scanf("%f",&principle) != 1) || (principle <= 0) )				// retrieve the loan priniciple while preventing inappropriate input
	{
		printf("The principle must be a number greater than zero, exclusive. Please try again!\n");
		return 0;
	}

	printf("Please enter the yearly interest rate on your loan (as a percentage): ");
	if( (scanf("%f",&interest) != 1) || (interest > 100) || (interest < 0) )	// retrive the yearly interest rate while preventing inappropriate input
	{
		printf("The yearly interest rate must be a number between 0 and 100, inclusive. Please try again!\n");
		return 0;
	}

	printf("Please enter the payment you plan to make every month (in dollars): ");
	if( (scanf("%f",&payment) != 1) || (payment < 0) )				// retrieve the monthly payment while preventing inappropriate input
	{
		printf("The monthly payment must be a number greater than zero, exclusive. Please try again!\n");
		return 0;
	}

	// we can begin the construction of our actual table

	interest = interest / 100;			// express interest in a decimal
	intCharge = principle * interest;		// we need to make sure the monthly payment is greater than the first interest charge
	intCharge = intCharge / 12;
	
	if( intCharge >= payment )			// stop the user early if we know the monthly payment is not enough
	{
		printf("\nYou will never be able to pay off this mortgage. Your monthly payment must be greater than $%.2f. Please try again!\n", intCharge);
		return 0;
	}

	cutoffPrinc = (payment*12) / (12+interest);	// we need to find the last principle that can be paid off with less than a full payment
							
	// ^ this eqn is from: principle + (principle*interest)/12 = payment
	
	printf("%15s %15s %15s %15s\n", "Month", "Payment", "Interest", "Balance");	// we can begin the actual table

	while( principle > cutoffPrinc)			// we will continue until our principle is less than the cutoff principle
	{	
		printf("%15.d %5s $%8.2f", countMonth, "", payment);			// we will always print the month number and the monthly payment

		intCharge = principle * interest;					// calculate the interest charged before the monthly payment
		intCharge = intCharge / 12;

		principle = principle - (payment - intCharge);				// principle decreases by the difference between payment and interest		

		printf("%6s $%8.2f %3s $%10.2f\n", "", intCharge, "",  principle);	// print out each value as right-justified and fix-sized
	
		countMonth++; 
	}

	countTotal = (countMonth-1) * payment;		// finding the total paid so far (excluding the last month)

	intCharge = principle * interest;		// calculate the interest charged before the monthly payment
        intCharge = intCharge / 12;

       	payment = principle + intCharge;		// we know the payment will be higher than the principle	
	principle = principle - (payment - intCharge);	// the principle should be zero!

	printf("%15.d %5s $%8.2f", countMonth, "", payment); 
	printf("%6s $%8.2f %3s $%10.2f\n", "", intCharge, "", principle); 
	
	printf("\nYou paid a total of $%.2f over %d years and %d months.\n\n", countTotal + payment, countMonth / 12, countMonth % 12);

	// we finish by printing the total amount paid and the time period necessary with the given monthly payment

	return 0;		
} 



