// CSE 20211
//
// gallery.c
//
// This program displays a set of 25 randomly generated fractals.
// The spacebar clears the screen and generates a new set.
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "gfx.h"

double pi = 3.14159;									// global pi

void draw_curve(int x, int y, int radius, double angleStart, double angleEnd)           // draw a curve based on its center (x,y), radius and angle range
{
        double theta;
	int inner;

        for( theta = angleStart; theta <= angleEnd; theta += .01 )			// draw a small line over every .01 radian
        {
		for( inner = 0; inner < radius; inner++ )				// draw smaller curves inside to create solid curves
		{
                	gfx_line( x+inner*cos(theta), y+inner*sin(theta), x+inner*cos(theta+.01), y+inner*sin(theta+.01) );
        	}
	}
}

void fractal_curve(int x, int y, int radius, double angle, int red, int green, int blue)	// recursive function that draws spiral circles 
{												// with center (x,y) and specified radius, RGB color
	if( radius < 2 )	return;

	gfx_color(red, green, blue);
	
	draw_curve(x, y, radius, 0, 2*pi);

	fractal_curve(x+(radius)*cos(angle), y+(radius)*sin(angle), 95*radius/100, angle+.415, red, green, blue);
}

int main( void )
{
        int Xheight = 1000;           	// x axis of window
        int Yheight = 750;              // y axis of window

	int number = 25;		// we will create 25 fractals

	int colors[number][3];		// arrays to keep track of fractal traits
	int radii[number];
	int center[number][2];
	double angle[number];

	int i = 0;			// counter
        int quit = 0;                   // quitting boolean

        char user;			// user input

	srand(time(NULL));

	for(i = 0; i < number; i++)
	{
		colors[i][1] = (rand() % 255);	// colors between 0 and 255
		colors[i][2] = (rand() % 255);
		colors[i][3] = (rand() % 255);
	
		radii[i] = 20 + (rand() % 30);	// radius between 20 and 50

		center[i][1] = 50 + (rand() % (Xheight-100));	// x-coordinate of center
		center[i][2] = 50 + (rand() % (Yheight-100));	// y-coordinate of center

		angle[i] = (rand() % 360) * (pi/180);	// angle between 0 and 2pi
	} 

        gfx_open(Xheight, Yheight, "Fractal Gallery");        	// opening graphics window
	gfx_clear_color(205, 175, 149);				// creating the sandy background
        gfx_color(255, 255, 255);                               // setting graphics color to white
	gfx_clear();

        while( 1 )
        {
		for(i = 0; i < number; i++)
		{
			fractal_curve( center[i][1], center[i][2], radii[i], angle[i], colors[i][1], colors[i][2], colors[i][3] );
		}

                user = gfx_wait();

                switch( user )
                {
                        case ' ':
                        {
                                gfx_clear();

				for(i = 0; i < number; i++)
        			{
                			colors[i][1] = (rand() % 255);  // colors between 0 and 255
                			colors[i][2] = (rand() % 255);
                			colors[i][3] = (rand() % 255);

                			radii[i] = 20 + (rand() % 30);  // radius between 20 and 50

                			center[i][1] = 50 + (rand() % (Xheight-100));      // x-coordinate of center
                			center[i][2] = 50 + (rand() % (Yheight-100));      // y-coordinate of center

                			angle[i] = (rand() % 360) * (pi/180);   // angle between 0 and 2pi
        			}

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

