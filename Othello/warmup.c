// CSE 20211
//
// warmup.c
//
// This program allows the user to enter 10 doubles as 
// an array. The mean and standard deviation of these 
// elements are then printed, along with the ordered set.
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int array_scan(double x[], int size)		// function that allows user input to array
{
	int i;
	int error = 0;

	printf("\nPlease enter 10 doubles, separated by <ENTER>:\n");	
	
	for(i = 0; i < size; i++)
	{
		if( scanf("%lf",&x[i]) != 1 )	// input one double to every array index
		{
			printf("Please enter decimal numbers. Try again!\n\n");	// makes sure the user enters a numeral
			error = 1;
			break;
		}
	}

	return error;				// make sure our program stops if the array is not complete
}

double array_mean(double x[], int size)		// calculate the mean of the values in a double array
{
	int i;
	double sum = 0;
	
	for(i = 0; i < size; i++)
	{
		 sum += x[i];			// summation of each term
	}

	return (sum/size);			// divide by size
}

double array_std(double x[], int size)		// calculate the standard deviation of the values in a double array
{
	int i;
	double sum = 0;
	double mean = array_mean(x, size);	// get mean of this array from the previous function

	for(i = 0; i < size; i++)
	{
		sum += pow(x[i]-mean,2);	// summation of the current term minus the mean, squared
	}
	
	return (sqrt(sum/size));		// divide by size because this is a population of doubles
}

void array_sort(double x[], int size)		// function that sorts an array from largest to smallest (bubble)
{
	int i = 0;				// counter
	int j = 0;				// counter
	double m = 0;				// placeholder
	int swaps = 0;				// keep track of swaps made

	for(i = 0; i < (size-1); i++)
	{
		for(j = 0; j < (size-1); j++)
		{
			if(x[j] < x[j+1])	// if current element is less than next, we need to swap
			{
				m = x[j];	// placeholders
				x[j] = x[j+1];
				x[j+1] = m;
				
				swaps++;
			}
		}

		if(swaps == 0)			// if no swaps were made, then stop sorting (it is in order)
		{
			break;
		}
		
		swaps = 0;
	}		
}

void array_print(double x[], int size)		// prints every element of the array 
{
	int i;
	
	for(i = 0; i < size; i++)
	{
		printf("%lf\n", x[i]);		// separated by a tab
	}
}

int main(void)
{
	int size = 10;

	double input[size];
	
	if( array_scan(input, size) != 1)								// allows for user input of a 10-element array
	{
		printf("\n-- RESULTS --\n");
	
		printf("\nMean of this array: %lf.\n", array_mean(input, size));			// prints mean of array elements

		printf("\nStandard deviation of this array: %lf.\n", array_std(input, size));		// prints standard deviation of array elements
	
		array_sort(input, size);								// this performs a bubble sort

		printf("\nBubble sort of this array:\n");

		array_print(input, size);								// prints all array elements

		printf("\n");
	}
}

