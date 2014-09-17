// CSE 20211
// Lab 4
//
// This program graphs A*x*sin(x/B)
// The user can decrease A with the 'A' key,
// increase A with the 'S' Key, decrease B with
// the 'Z' key, or increase B with the 'X' key
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gfx.h"

int circled = 1;		// this is a boolean to determine when our local maxes have been circled
int ymax = 0;			// our ymax should be global in order to determine its value after multiple function calls

void draw_curve(int x, int y, int radius, double angleStart, double angleEnd)	// draws a circular curve within the angle range specified, with center at (x, y)
{
	double theta;

	for( theta = angleStart; theta <= angleEnd; theta += .01 )
	{
		gfx_line( (x+radius*cos(theta)), (y+radius*sin(theta)), (x+radius*cos(theta+.01)), (y+radius*sin(theta+.01)) );
	}
}

void draw_zero(int x, int y, int height)					// draws a zero with the specified height, with its top at (x, y)
{
	float pi = 3.14159;

	int width;
	int radius;

	width = height / 2;			// width of 0 is dependent upon specified height
	radius = height / 4;			// radius of the top and button curves

	draw_curve( x, y+radius, radius, pi, 2*pi );		// top of zero
	draw_curve( x, y+3*radius, radius, 0, pi );		// bottom of zero
	
	gfx_line( x+radius, y+radius, x+radius, y+3*radius );	// right side of zero
	gfx_line( x-radius, y+radius, x-radius, y+3*radius );	// left side of zero
	gfx_line( x+radius, y+radius, x-radius, y+3*radius );	// middle of zero
}

void draw_one(int x, int y, int height)						// draws a one with the specified height, with its top at (x, y)
{
	int width;
	int radius;	

	width = height / 2;
	radius = height / 4;

	gfx_line( x-(width/4), y+(height/5), x, y );			// head of the one
	gfx_line( x, y, x, y+height );					// body of the one
	gfx_line( x-radius, y+height, x+radius, y+height );		// bottom of the one
}

void draw_two(int x, int y, int height)						// draws a two with the specified height, with its top at (x, y)
{
	float pi = 3.14159;

	int width;
	int radius;

	width = height / 2;
	radius = height / 4;

	draw_curve( x, y+radius, radius, pi, 2*pi );		// top of the two

	gfx_line( x+radius, y+radius, x-radius, y+height );	// diagonal of the two
	gfx_line( x-radius, y+height, x+radius, y+height );	// bottom of the two
}

void draw_three(int x, int y, int height)                                       // draws a three with the specified height, with its top at (x, y)
{
        float pi = 3.14159;

        int width;
        int radius;
        int mid;

        width = height / 2;
        mid = height / 4;
        radius = height / 3;

        draw_curve( x, y+(2*height/3), radius, -2*pi/3, 2*pi/3 );               // body of the three

        gfx_line( x-mid, y, x+mid, y );                                         // top of the three
        gfx_line( x+mid, y, x-mid, y+height-radius-(sin(pi/3)*radius) );        // diagonal of the three
}

void draw_four(int x, int y, int height)                                        // draws a four with the specified height, with its top at (x, y)
{
        int width;
        int radius;

        width = height / 2;
        radius = height / 4;

        gfx_line( x+radius, y, x+radius, y+height );                            // right side of four
        gfx_line( x-(3*radius/4), y, x-radius, y+(3*height/7) );                // diagonal of the four
        gfx_line( x-radius, y+(3*height/7), x+radius, y+(3*height/7) );         // middle of the four
}

void draw_five(int x, int y, int height)                                        // draws a five with the specified height, with its top at (x, y)
{
        float pi = 3.14159;

        int width;
        int radius;
        int mid;

        width = height / 2;
        mid = height / 4;
        radius = height / 3;

        draw_curve( x, y+(2*height/3), radius, -2*pi/3, 2*pi/3 );               // body of the five

        gfx_line( x-(1/3)*mid, y, x+mid, y );                                   // top of the five
        gfx_line( x+(1/3)*mid, y, x-mid, y+height-radius-(sin(pi/3)*radius) );  // diagonal of the five
}

void draw_six(int x, int y, int height)     					// draws a six with the specified height, with its top at (x, y)
{
        float pi = 3.14159;

        int width;
        int radius;

        width = height / 2;
        radius = height / 4;

        draw_curve( x, y+radius, radius, pi, 2*pi );		// top of the six
	draw_curve( x, y+(3*radius), radius, 0, 2*pi);		// body of the six

        gfx_line( x-radius, y+radius, x-radius, y+3*radius );	// top of the five
}

void draw_seven(int x, int y, int height)					// draws a seven with the specified height, with its top at (x, y)
{
        int width;
        int radius;

        width = height / 2;
        radius = height / 4;

        gfx_line( x-radius, y, x+radius, y );   				// top of the seven
	gfx_line( x+radius, y, x-radius, y+height);				// body of the seven
	gfx_line( x-(radius/2), y+(height/2), x+(radius/2), y+(height/2));	// middle of the seven
}

void draw_eight(int x, int y, int height)                    			// draws an eight with the specified height, with its top at (x, y)
{
        float pi = 3.14159;

        int width;
        int radius;

        width = height / 2;
        radius = height / 4;

        draw_curve( x, y+radius, radius, 0, 2*pi );		// top of the eight
        draw_curve( x, y+(3*radius), radius, 0, 2*pi);		// bottom of the eight
}

void draw_nine(int x, int y, int height)					// draws a nine with the specified height, with its top at (x, y)
{
	float pi = 3.14159;

	int width;
	int radius;

	width = height / 2;
	radius = height / 4;

	draw_curve( x, y+radius, radius, 0, 2*pi );		// body of the nine
	draw_curve( x, y+(3*radius), radius, 0, pi);		// bottom of the nine

	gfx_line( x+radius, y+radius, x+radius, y+3*radius );	// side of the nine
}

void draw_decimal(int x, int y, int height)					// draws a decimal inside a block of specified height, with its top at (x, y)
{
	float pi = 3.14159;

	int width;
	int radius;

	width = height / 2;
	radius = height / 10;

	draw_curve( x, y+height-radius, radius, 0, 2*pi );	// decimal point
}

void draw_numeral(int x, int y, int n, int height)				// draws a single numeral with specified height and upper right at (x, y)
{
	switch( n )
	{
		case 0: 
		{
			draw_zero(x, y, height);
			break;
		}
		case 1: 
		{
			draw_one(x, y, height);
			break;
		}
		case 2: 
		{
			draw_two(x, y, height);
			break;
		}
		case 3: 
		{
			draw_three(x, y, height);
			break;
		}
		case 4: 
		{
			draw_four(x, y, height);
			break;	
		}
		case 5: 
		{
			draw_five(x, y, height);
			break;
		}
		case 6: 
		{
			draw_six(x, y, height);
			break;
		}
		case 7: 
		{
			draw_seven(x, y, height);
			break;
		}
		case 8: 
		{
			draw_eight(x, y, height);
			break;
		}
		case 9: 
		{
			draw_nine(x, y, height);
			break;
		}
	}
}

void draw_integer(int ourInt, int x, int y, int height)	// draws the specified (0-999999) integer with specified height at the upper-left point (x,y) 
{
	if( ourInt >= 0 )
	{
		draw_numeral(x-height/2, y, ((((ourInt % 100000) % 10000) % 1000) % 100) % 10, height);		// ones digit
	}
	
	if( ourInt >= 10 )
	{
		draw_numeral(x-3*height/2, y, ((((ourInt % 100000) % 10000) % 1000) % 100) / 10, height);	// tens digit
	}
	
	if( ourInt >= 100 )
	{
		draw_numeral(x-5*height/2, y, (((ourInt % 100000) % 10000) % 1000) / 100, height);		// hundreds digit	
	}

	if( ourInt >= 1000 )
	{
		draw_numeral(x-7*height/2, y, ((ourInt % 100000) % 10000) / 1000, height);			// thousands digit
	}
	
	if( ourInt >= 10000 )
	{
		draw_numeral(x-9*height/2, y, (ourInt % 100000) / 10000, height);				// ten thousands digit
	}
	
	if( ourInt >= 100000 )
	{
		draw_numeral(x-11*height/2, y, ourInt / 100000, height);					// hundred thousands digit
	}
}

void draw_y(int x, int y, int height)					// draws "Y = " with the specified height and upper middle point (x,y)	
{
	int width = height;
	int mid = height / 2;

	gfx_line( x-mid, y, x-(mid/2), y+mid );			// upper left of Y
	gfx_line( x, y, x-(mid/2), y+mid );			// upper right of Y
	gfx_line( x-(mid/2), y+mid, x-(mid/2), y+height);	// body of Y
	
	gfx_line( x, y+(2*mid/3), x+mid, y+(2*mid/3) );		// upper equals sign
	gfx_line( x, y+(4*mid/3), x+mid, y+(4*mid/3) );		// upper equals sign
}

void draw_function(int xEnd, int xAxisPosition, int xHeight, int yHeight, float A, float B)// draws the function A*x*sin(x/B) in the x-range of 0 to xEnd
{
	int c;

	float pi = 3.14159;

	float x1 = 0;			// point 1
	float y1 = 0;

	float x2 = 0;			// point 2
	float y2 = 0;	

	for( c = 0; c <= xEnd; c += 1 )						// we will draw a line every two pixels
	{
		x1 = x2;
		y1 = y2;

		x2 = c;
		y2 = xAxisPosition - A*(x2*(pi/60))*sin((x2/(B))*(pi/60));	// every increment in x equals 63 degrees

		gfx_line( x1, y1, x2, y2 );
	}
}

void draw_maxes(int xEnd, int xAxisPosition, int xHeight, int yHeight, float A, float B)// draws the function A*x*sin(x/B) in the x-range of 0 to xEnd
{
	int c;

	float pi = 3.14159;

	float x1 = 0;			// point 1
	float y1 = 0;

	float x2 = 0;			// point 2
	float y2 = 0;	

	circled = 0;

	for( c = 0; c <= xEnd; c += 1 )					// we will draw a line every two pixels
	{
		x1 = x2;
		y1 = y2;

		x2 = c;
		y2 = A*(x2*(pi/60))*sin((x2/B)*(pi/60));

		if( y2 < 0 )	ymax = 0;				// make sure that ymax is reset to we are getting local maximums
	
		if( y2 > ymax )						// keep track of the local ymax in order to circle and label it
		{
			ymax = y2;
			circled = 0;	
		}
		
		if( y2 < ymax )						// once ymax has been established, when y decreases we should circle the point before
		{
			if( circled == 0 )
			{
				draw_curve(x1, xAxisPosition-y1, yHeight/50, 0, 2*pi);
				draw_y(x1+(xHeight/100), xAxisPosition-y1-(yHeight/25), (yHeight/75));
				draw_integer(y1, x1+(xHeight/25), xAxisPosition-y1-(yHeight/25), (yHeight/75));	// writes out the local maximum
				circled = 1;
			}
		}
	}
}


int main(void)			// actually draw the graph!
{
	float A = 10;			// our function constants
	float B = 5;

	int xHeight = 1500;		// pixel size of the window
	int yHeight = 1000;		

	char user;			// user input

	int quit = 0;			// quitting boolean
	
	gfx_open(xHeight, yHeight, "Graphing Calculator");

	while( 1 )
	{
		gfx_clear();

		gfx_line(0, yHeight/2, xHeight, yHeight/2);				// x-axis
		
		draw_function(xHeight, yHeight/2, xHeight, yHeight, A, B);		// draw our function  
		draw_maxes(xHeight, yHeight/2, xHeight, yHeight, A, B);

		user = gfx_wait();
		
		switch( user )
		{
			case 'a':
			{
				A /= 2;
				ymax = 0;
				break;
			}
			case 's':
			{
				A *= 2;	
				ymax = 0;
				break;
			}
			case 'z':
			{
				B /= 2;
				ymax = 0;
				break;
			}
			case 'x':
			{
				B *= 2;
				ymax = 0;
				break;
			}
			case 'q':
			{
				quit = 1;
				ymax = 0;
				break;
			}
		}
	
		if( quit == 1 )
		{
			break;
		}
	
		gfx_flush();
	}
}

