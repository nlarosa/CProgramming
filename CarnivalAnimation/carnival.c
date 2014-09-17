// CSE 202110
//
// This program displays a "roller coaster" 
// that involves four dimensions of motion. 
// The user can end the animation and close
// the window with the 'q' key.
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gfx.h"

float ourAngle1 = 0;		// these four global variables keep track of the four dimensions of motion
float ourAngle2 = 0;
float ourAngle3 = 0;
float ourAngle4 = 0;

void draw_curve(int x, int y, int radius, double angleStart, double angleEnd)   // draws a circular curve within the angle range specified, with center at (x, y)
{
	double theta;

	for( theta = angleStart; theta <= angleEnd; theta += .01 )
	{
		gfx_line( (x+radius*cos(theta)), (y+radius*sin(theta)), (x+radius*cos(theta+.01)), (y+radius*sin(theta+.01)) );
	}
}

void draw_rotating_seats(int x, int y, int radius)				// draws a rotating group of four circular "seats"
{
	float pi = 3.14159;
	
	gfx_color(238, 221, 130);

	draw_curve( x, y, radius/4, 0, 2*pi );

	draw_curve( x+(5*radius/8)*cos(ourAngle1), y+(5*radius/8)*sin(ourAngle1), radius/8, 0, 2*pi );
	draw_curve( x+(5*radius/8)*cos(ourAngle1+(pi/2)), y+(5*radius/8)*sin(ourAngle1+(pi/2)), radius/8, 0, 2*pi );
	draw_curve( x+(5*radius/8)*cos(ourAngle1+(pi)), y+(5*radius/8)*sin(ourAngle1+(pi)), radius/8, 0, 2*pi );
	draw_curve( x+(5*radius/8)*cos(ourAngle1+(3*pi/2)), y+(5*radius/8)*sin(ourAngle1+(3*pi/2)), radius/8, 0, 2*pi );

	gfx_line(x+(radius/4)*cos(ourAngle1),y+(radius/4)*sin(ourAngle1),x+(3*radius/4)*cos(ourAngle1),y+(3*radius/4)*sin(ourAngle1));
	gfx_line(x+(radius/4)*cos(ourAngle1+pi/2),y+(radius/4)*sin(ourAngle1+pi/2),x+(3*radius/4)*cos(ourAngle1+pi/2),y+(3*radius/4)*sin(ourAngle1+pi/2));
	gfx_line(x+(radius/4)*cos(ourAngle1+pi),y+(radius/4)*sin(ourAngle1+pi),x+(3*radius/4)*cos(ourAngle1+pi),y+(3*radius/4)*sin(ourAngle1+pi));
	gfx_line(x+(radius/4)*cos(ourAngle1+3*pi/2),y+(radius/4)*sin(ourAngle1+3*pi/2),x+(3*radius/4)*cos(ourAngle1+3*pi/2),y+(3*radius/4)*sin(ourAngle1+3*pi/2));

	ourAngle1 += .10;			// we will iterate our angle until the loop is broken
}

void draw_rotating_group(int x, int y, int radius) 				// draws an rotating group of seats that moves in a circle of specified radius
{
	float pi = 3.14159;

	draw_rotating_seats( x+(radius*cos(ourAngle2)), y+(radius*sin(ourAngle2)), radius*2 );		// draws a group of seats
	
	gfx_color(173, 255, 47);
	gfx_line( x, y, x+(radius*cos(ourAngle2)), y+(radius*sin(ourAngle2)) );				// a line will connect the group to the center
	
	ourAngle2 += .05;			// increment our angle 
}

void draw_rotating_whole(int x, int y, int radius)				// draws the entire rotating structure that contains one rotating group
{
	float pi = 3.14159;

	draw_curve( x, y, radius/10, 0, 2*pi );
	draw_rotating_group( x+(radius*cos(ourAngle3)), y+(radius*sin(ourAngle3)), radius/5 );		// the line connects to the center of the group

	gfx_color(0, 250, 154);
	gfx_line( x+(radius/10)*cos(ourAngle3), y+(radius/10)*sin(ourAngle3), x+(radius*cos(ourAngle3)), y+(radius*sin(ourAngle3)) ); 
	
	ourAngle3 += .01;
}

void draw_springing_whole(int x, int y, int xHeight, int yHeight)		// draws the entire rotating structure as if it were attached to a spring
{										// with the top of the spring attached at (x,y)
	float pi = 3.14159;

	int radius = yHeight / 5;

	gfx_color(255, 69, 0);
	gfx_line( x-(xHeight/100), 0, x-(xHeight/100), y );
	gfx_line( x+(xHeight/100), 0, x+(xHeight/100), y );
	gfx_line( x-(xHeight/100), y, x+(xHeight/100), y );

	draw_rotating_whole( x, y+(radius*sin(ourAngle4))+(13*radius/7), radius );
	
	gfx_color(178, 34, 34);
	gfx_line( x, y, x, y+(radius*sin(ourAngle4))+(13*radius/7) );		// connect the rotating group to the bar at the top
	
	ourAngle4 += .10;
}

int main(void)
{
	int xHeight = 500;
	int yHeight = 750;

	char user;

	int quit = 0;

	gfx_open(xHeight, yHeight, "Carnival Ride");

	while( 1 )
	{
		gfx_clear();

		draw_springing_whole( xHeight/2, yHeight/8, xHeight, yHeight );
	
		if( gfx_event_waiting() )			// only interrupt when the user presses 'q'
		{
			user = gfx_wait();
		
			if( user == 'q' )
			{
				quit = 1;
				break;
			}
		}

		if( quit == 1 )
		{
			break;
		}

		usleep(10000);

		gfx_flush();
	}	
}

