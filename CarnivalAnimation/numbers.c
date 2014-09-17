// CSE 20211
//
// This program is a numeric typewriter
// 
// Press the keys 0-9 to display that number
// at the current mouse location
// 
// The '=' key will double the size of the 
// numbers, and '-' will halve their size
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gfx.h"

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

void draw_three(int x, int y, int height)					// draws a three with the specified height, with its top at (x, y)
{
	float pi = 3.14159;

        int width;
        int radius;
	int mid;

        width = height / 2;
	mid = height / 4;
        radius = height / 3;

        draw_curve( x, y+(2*height/3), radius, -2*pi/3, 2*pi/3 );		// body of the three

        gfx_line( x-mid, y, x+mid, y );    	 				// top of the three
        gfx_line( x+mid, y, x-mid, y+height-radius-(sin(pi/3)*radius) );     	// diagonal of the three
}
		
void draw_four(int x, int y, int height)					// draws a four with the specified height, with its top at (x, y)
{
        int width;
        int radius;

        width = height / 2;
        radius = height / 4;

        gfx_line( x+radius, y, x+radius, y+height );				// right side of four
        gfx_line( x-(3*radius/4), y, x-radius, y+(3*height/7) );		// diagonal of the four
	gfx_line( x-radius, y+(3*height/7), x+radius, y+(3*height/7) );		// middle of the four
}

void draw_five(int x, int y, int height)					// draws a five with the specified height, with its top at (x, y)
{
        float pi = 3.14159;

        int width;
        int radius;
        int mid;

        width = height / 2;
        mid = height / 4;
        radius = height / 3;

        draw_curve( x, y+(2*height/3), radius, -2*pi/3, 2*pi/3 );		// body of the five

        gfx_line( x-(1/3)*mid, y, x+mid, y );					// top of the five
        gfx_line( x+(1/3)*mid, y, x-mid, y+height-radius-(sin(pi/3)*radius) ); 	// diagonal of the five
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

int main(void)
{
	float pi = 3.14159;

	int Xpos;					// keeping track of where the user mouse clicked
	int Ypos;
		
	int Xheight = 500;
	int Yheight = 500;
	
	int size = 5;					// divide the page height by this number to find the height of the numerals (initially 100 pixels high)

	char user;					// user input as a char
	int userNumber;					// user input as an integer
	
	int quit = 0;					// quit program boolean

	gfx_open( Xheight, Yheight, "Numeric Typewriter" );
	gfx_color( 255, 255, 255);

	while ( 1 )
	{	
		user = gfx_wait();

		switch( user )
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':				
			{
				Xpos = gfx_xpos();
				Ypos = gfx_ypos();

				userNumber = user - 48;		// converting from ASCII to actual value

				draw_numeral( Xpos, Ypos, userNumber, Xheight/size );
	
				break;
			}
			case '=':
			{
				size /= 2;			// double the height
				break;
			}
			case '-':
			{
				size *= 2;			// halve the height
				break;
			}
			case ' ':
			{
				gfx_clear();
				break;
			}
			case 'q':
			{
				quit = 1;
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

