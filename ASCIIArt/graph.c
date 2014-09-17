// Nicholas LaRosa
// Monday Lab Section

#include <stdio.h>
#include <math.h>

int main(void)			// we will plot the function y = sin(2sin(2sin(2sin(x)))) using ASCII art
{				// we will have a x-acis that runs vertically down the page (we have positive and negative values)
	float x = 0;
	float y = 0;

	float initialx = x;	// range from 0 to 4pi
	float finalx = 4*3.142;

	float miny = 0;		// keep track of the minimum value
	float maxy = 0;		// keep track of the maximum value

	float minx = 0;		// keep track of the x value that corresponds to the maximum y-value
	float maxx = 0;		// keep track of the x value that corresponds to the minimum y-value

	int count = 0;		// count where we are on the axis
	int length;		// placeholder to compute number of characters to print

	printf("\nPlot of y = sin(2sin(2sin(2sin(x)))) from x = 0 to 12*pi\n\n");
	printf("%5sX%5sY\t%20sx-axis\n", " ", " ", " "); 				// formatting our header correctly
	
	while( x <= finalx )	// our range will be from .05 to 10
	{
		y = 2*sin(x);		// we need the base 10 logarithm and power function from the math library
		y = 2*sin(y);
		y = 2*sin(y);
		y = sin(y);

		printf("%6.2f%6.2f\t", x, y);

		length = y*20;		// prepare x and y for ASCII representation	
		length = roundf(length);
		
		length = (int)length;	// we need to cast so that our length is definitely a solid integer
	
		if( y >= 0 )		// print out after the x-axis (right)
		{
			printf("%22s|", " ");		// first 23 characters include 22 spaces and 1 "|" to represent the x-axis
			
			count = 1;

			while( count <= length )	// our axis is 45 characters long (22 characters on each side of the x-axis)
			{
				printf("#");
				count++;
			}		
		}
		else			// print out before the x-axis (left)
		{
			printf("%*s", 22 + length, " ");	// the number of spaces before the graph will depend on the y-value		
								// since our "length" is negative, add it to 20 to find difference
			count = 1;

			while( count <= (-1*length) )		// print a # to fill up space up to the value of y
			{
				printf("#");
				count++;
			}	

			printf("|");				// end with our x-axis
		}

		if( y >= maxy)					// find out if this new y value is a maximum or minimum
		{
			maxy = y;
			maxx = x;
		}
		
		if( y <= miny)
		{
			miny = y;
			minx = x;
		}
	
		printf("\n");					// make sure to create a new line
		x += .1;
	}

	printf("\nThe minimum of %.2f occurred at x = %.2f", miny, minx);
	printf("\nThe maximum of %.2f occurred at x = %.2f\n\n", maxy, maxx);

	return 0;
}

