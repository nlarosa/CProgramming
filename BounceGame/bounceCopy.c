// CSE 20211
//
// This program is a symbolic typewriter, where a mouse click creates a
// blue square, the 'c' button creates a white circle, the 't' button creates
// a green triangle, and buttons '3' through '9' create polygons with the
// corresponding number of sides. The space bar clears the screen
//
// Nicholas LaRosa

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "gfx.h"

int main(void)			// we will be constructing an animation of a ball bouncing around the window
{
	int mousePosX;		// we need to find the position of the mouse when clicked
	int mousePosY;

	int screenX = 500;	// variable size of the graphics library
	int screenY = 500;

	float x = screenX/2;	// coordinates of the ball
	float y = screenY/2;

	float x1;		// points for plotting the ball itself
	float y1;
	
	float x2;		// points for plotting the ball itself
	float y2;

	float vx = 10.0;	// velocity of the ball in pixels/sec
	float vy = 15.0; 

	float min = 5.0;	// our velocity will be between 5 and 20 pixels per second
	float max = 20.0;
	float signX = 1.0;	// our velocities can also be negative
	float signY = 1.0;
	float random = 0;

	float deltaT = 0.01;	// change in time between each frame (in seconds)

	float pi = atan(1)*4;	// constant for pi

	char user;              // this will be the value of the user input
	
	int c = 0;		// counter for looping
	int radius = 10;

        srand(time(NULL));   	// random integer seed
	
	gfx_open(screenX, screenY, "Bouncing Ball");

	gfx_color(255, 255, 255); 	// our ball will be white

	while( 1 )
	{
		gfx_clear();

		if( gfx_event_waiting() )	// we have user input
		{
			user = gfx_wait();

			if( user == 1 )		// we have a mouse click
			{	
				x = gfx_xpos();	// we will place the ball where the mouse was clicked
				y = gfx_ypos();

				random = rand() % 2;		// generate a random int to determine the new sign of our velocity
	
				if( random == 0 ) 
				{	
					signX = -1.0;
				}
				else 
				{
					signX = 1.0;
				}	

				random = rand() % 2;            // generate a random int to determine the new sign of our velocity

                                if( random == 0 ) 
				{
					signY = -1.0;
				}
                                else 
				{
					signY = 1.0;
				}

				vx = signX * (min + (rand() % (int)(max-min+1)));	// generating our random velocities
				vy = signY * (min + (rand() % (int)(max-min+1)));
			}
			else if( user == 'q' )
			{
				break;
			}
		}

		if( user == 'q' )
		{
			break;
		}

		if( (x < radius) || ((x + radius) > screenX) )
		{
			vx = -1.0 * vx;			// if the new plot is going to be out of range then we need to "bounce"
			
			if( (y < radius) || ((y + radius) > screenY) )		// we are stuck in a corner, help out
			{
				x = x - screenX;
				y = y - screenY;
			} 				
		}	
		if( (y < radius) || ((y + radius) > screenY) )
                {
                        vy = -1.0 * vy;			// if the new plot is going to be out of range then we need to "bounce"
                
			if( (x < radius) || ((x + radius) > screenX) )		// we are stuck in a corner, help out
			{
				x = x - screenX;
				y = y - screenY;
			} 				
		}

		x = x + (vx)*(deltaT);			// new x and y positions
		y = y + (vy)*(deltaT);	

		x2 = x + radius;			// this is the first point plotted on the ball
		y2 = y;

		for( c = 0; c <= 360; c++ )		// plotting the actual ball
		{
			x1 = x2;			// store our previous value as our initial line start
			y1 = y2;
	
			x2 = x + (cos(c*pi/180)*radius);	// draw the circle point by point
			y2 = y + (sin(c*pi/180)*radius);
			
			gfx_line(x1, y1, x2, y2);
		}

		gfx_flush();					
		
		usleep(10000);
	}
}

