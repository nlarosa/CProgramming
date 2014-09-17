// CSE 20211
//
// This program is a symbolic typewriter, where a mouse click creates
// a square circle, the 'c' button creates a white circle, the 't' button
// creates a green triangle, and number '3' through '9' create polygons 
// with the specified number of sides
//
// Nicholas LaRosa

#include <stdio.h>	
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "gfx.h"

int main(void)			// we will be constructing a symbolic typewriter using a basic graphics library
{
	int mousePosX;		// mouse point position in x and y directions
	int mousePosY;

	int screenX = 900;	// screen resolution in pixels
	int screenY = 900;

	float x1;		// position 1
	float y1;

	float x2;		// position 2
	float y2; 

	float radians;		// need radians and radius when dealing with polar coordinated
	float radius;

	float pi = atan(1)*4;	// pi constant
	
	int min = 0;		// minimum number of degrees
	int c = 0;		// counter for for loops
	int randomDegrees = 0;	// random integer degree
	int polygon = 0;	// place for number of polygon sides

	char user;		// this will be the value of the user input 

	srand(time(NULL));	// random integer seed

	// begin symbolic typewriter

	gfx_open(screenX, screenY, "Symbolic Typewriter");

	while( 1 )
	{
		user = gfx_wait();		// waiting for a user-given symbol

		switch( user )
		{	
			case 1:			// mouse click, we will print a blue square outline
			{
				gfx_color(0, 0, 255);		// changing color to blue

				radius = 25;

				mousePosX = gfx_xpos();		// storing the current mouse position
				mousePosY = gfx_ypos();

				x1 = mousePosX + radius;	// upper right point
				y1 = mousePosY + radius;

				x2 = mousePosX - radius;	// upper left point
				y2 = mousePosY + radius;

				gfx_line((int)x1, (int)y1, (int)x2, (int)y2);	// top line		

				x1 = mousePosX + radius;	// upper right point
				y1 = mousePosY + radius;

				x2 = mousePosX + radius;       	// lower right point
				y2 = mousePosY - radius;

				gfx_line((int)x1, (int)y1, (int)x2, (int)y2);  	// right line

				x1 = mousePosX + radius;       	// lower right point
				y1 = mousePosY - radius;

				x2 = mousePosX - radius;       	// lower left point
				y2 = mousePosY - radius;

				gfx_line((int)x1, (int)y1, (int)x2, (int)y2); 	// lower line

				x1 = mousePosX - radius;       	// lower left point
				y1 = mousePosY - radius;

				x2 = mousePosX - radius;       	// upper left point
				y2 = mousePosY + radius;

				gfx_line((int)x1, (int)y1, (int)x2, (int)y2);	// left line
			
				gfx_flush();		// actually draw the square
			
				break;
			}

			case 't':		// display a green triangle outline	
			{
				gfx_color(0, 255, 0);		// changing color to green

				radius = 25;

                                mousePosX = gfx_xpos();		// storing the current mouse position
                                mousePosY = gfx_ypos();

                                x1 = mousePosX;			// upper point
                                y1 = mousePosY - radius;

                                x2 = mousePosX + radius;	// lower right point
                                y2 = mousePosY + radius;

                                gfx_line((int)x1, (int)y1, (int)x2, (int)y2);   // right line

                                x1 = mousePosX + radius;	// lower right point
                                y1 = mousePosY + radius;

                                x2 = mousePosX - radius;      	// lower left point
                                y2 = mousePosY + radius;

                                gfx_line((int)x1, (int)y1, (int)x2, (int)y2);   // bottom line
			
				x1 = mousePosX - radius;	// lower left point
                                y1 = mousePosY + radius;

                                x2 = mousePosX;             	// upper point
                                y2 = mousePosY - radius;

                                gfx_line((int)x1, (int)y1, (int)x2, (int)y2);   // left line

				gfx_flush();
			
				break;
			}

			case 'c':		// display a white circle outline
			{
				gfx_color(255, 255, 255);	// change the color to white
			
				radius = 25;			// circle radius of 5 pixels

				mousePosX = gfx_xpos();
				mousePosY = gfx_ypos();

				x2 = mousePosX + radius;		// determine the first point
				y2 = mousePosY;
			
				for( c = 0; c <= 360; c++ )		// go through an entire circle (convert to radians)
				{
					x1 = x2;			// assign the last point to be the first point for the next line
					y1 = y2;
		
					x2 = mousePosX + (cos(c*pi/180)*radius);
					y2 = mousePosY + (sin(c*pi/180)*radius);

					gfx_line((int)x1, (int)y1, (int)x2, (int)y2);
				}

				gfx_flush();

				break;
			}	

			case '3': 
			case '4': 
			case '5': 
			case '6': 
			case '7': 
			case '8': 
			case '9':				// print a polygon with the alotted number of sides
			{
				switch ( user )			// find the integer number of sides
				{
					case '3':
					{
						polygon = 3;
						min = 80;	// setting the minimum degrees between each point
						break;		// the angle must be between this min and 360/sides
					}
					case '4':
					{
						polygon = 4;
						min = 65;
						break;
					}
					case '5':
					{
						polygon = 5;
						min = 62;
						break;
					}
					case '6':
					{
						polygon = 6;
						min = 55;
						break;
					}
					case '7':
					{
						polygon = 7;
						min = 50;
						break;
					}
					case '8':
					{
						polygon = 8;
						min = 45;
						break;
					}
					case '9':
					{
						polygon = 9;
						min = 39;
						break;
					}
				}
	
				gfx_color(150, 0, 150);		// change the color to purple

				radius = 50;
				randomDegrees = 0;

				mousePosX = gfx_xpos();
				mousePosY = gfx_ypos();

				x2 = mousePosX + radius;		// determine the first point
				y2 = mousePosY;

				for( c = 1; c < polygon; c++ )		// making only the specified number of points
				{
					x1 = x2;			// assign the last point to be the first point for the next line
					y1 = y2; 
					
					randomDegrees = randomDegrees + (min + (rand() % ((360 / polygon)-min+2)));	// random integer degree limit

					// the degrees added are in the range of min to max, where the max is dependent on the number of sides

					x2 = mousePosX + (cos(randomDegrees*pi/180)*radius);
					y2 = mousePosY + (sin(randomDegrees*pi/180)*radius);

					gfx_line((int)x1, (int)y1, (int)x2, (int)y2);
				}
				
				x1 = x2;			// for the last point we need to make sure it returns to the original point
				y1 = y2;

				x2 = mousePosX + radius;
				y2 = mousePosY;
	
				gfx_line((int)x1, (int)y1, (int)x2, (int)y2);
			
				gfx_flush();

				break;
			}			

			case ' ':		// clear the graphics window
			{
				gfx_clear();
			
				break;
			}

			case 'q':		// quit the graphics window		
			{
				break;
			}
		}

		if( user == 'q' )		// quitting actual while loop
		{
			break;
		}
	}
}

