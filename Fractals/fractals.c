// CSE 20211
//
// fractals.c
//
// This program displays a fractal for each of the number keys
// 1 through 8. The 'q' key exits the program.
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gfx.h"

const double pi = 3.14159;								// global pi

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)			// draw a triangle based on its three corners 
{
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x1, y1);
}

void draw_square(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)	// draw a square based on its four corners
{
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x4, y4);
	gfx_line(x4, y4, x1, y1);
}

void draw_curve(int x, int y, int radius, double angleStart, double angleEnd)		// draw a curve based on its center (x,y), radius and angle range
{
	double theta;

	for( theta = angleStart; theta <= angleEnd; theta += .01 )
	{
		gfx_line( x+radius*cos(theta), y+radius*sin(theta), x+radius*cos(theta+.01), y+radius*sin(theta+.01) );
	}
}

void draw_pentagon(int x, int y, int radius)						// draw a pentagon based on its center (x,y) and radius
{
	double theta;
	double angleStart = pi/2;

	for( theta = angleStart; theta <= 5*pi/2; theta += 2*pi/5 )
	{
		gfx_line(x, y, x+radius*cos(theta), y+radius*sin(theta));
	}
}

void fractal_triangle(int x1, int y1, int x2, int y2, int x3, int y3)			// recursive triangle based on its three corners
{
	if( abs(x1-x2) < 3 ) 	return;							// base case - triangles too small 
	
	draw_triangle(x1, y1, x2, y2, x3, y3);						// needs to draw a triangle at every iteration	
	
	fractal_triangle(x1, y1, (x1+x3)/2, (y1+y3)/2, (x1+x2)/2, (y1+y2)/2);	
	fractal_triangle((x1+x2)/2, (y1+y2)/2, x1, y3, x2, y2);		
	fractal_triangle((x1+x3)/2, (y1+y3)/2, x3, y3, x1, y3);		
}

void fractal_square(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)	// recursive square based on its four corners
{
	if( abs(x1-x2) < 3 ) 	return;							// base case - squares too small

	int radius = (x2-x1)/4;								// this value will help in construction of corner squares
	
	draw_square(x1, y1, x2, y2, x3, y3, x4, y4);					// draw a square every iteration

	fractal_square(x1-radius, y1-radius, x1+radius, y1-radius, x1+radius, y1+radius, x1-radius, y1+radius);		// and four corner squares
	fractal_square(x2-radius, y2-radius, x2+radius, y2-radius, x2+radius, y2+radius, x2-radius, y2+radius);
	fractal_square(x3-radius, y3-radius, x3+radius, y3-radius, x3+radius, y3+radius, x3-radius, y3+radius);
	fractal_square(x4-radius, y4-radius, x4+radius, y4-radius, x4+radius, y4+radius, x4-radius, y4+radius);
}

void fractal_squareSpiral(int x, int y, int radius, double angle)			// recursive spiral of squares based on its center (x,y) and radius
{
	if( radius < 5 ) 	return;							// base case - radius too small
	
	draw_square(x-radius*cos(angle)-(radius/6), y-radius*sin(angle)-(radius/6),\
			x-radius*cos(angle)+(radius/6), y-radius*sin(angle)-(radius/6),\
				x-radius*cos(angle)+(radius/6), y-radius*sin(angle)+(radius/6),\
					x-radius*cos(angle)-(radius/6), y-radius*sin(angle)+(radius/6));	// draw a square every iteration
	
	fractal_squareSpiral(x, y, 9*radius/10, angle-(pi/6));				// and a recursive spiral
}

void fractal_circle(int x, int y, int radius)						// recursive circle based on its center (x,y) and radius
{
	if( radius < 2 ) 	return;							// base case - radius too small

	double theta = 0;

	draw_curve(x, y, radius, 0, 2*pi);						// draw one circle
	
	fractal_circle(x+radius*cos(theta+0*(pi/3)), y+radius*sin(theta+0*(pi/3)), radius/3);	// and six others around its edge
	fractal_circle(x+radius*cos(theta+1*(pi/3)), y+radius*sin(theta+1*(pi/3)), radius/3);
	fractal_circle(x+radius*cos(theta+2*(pi/3)), y+radius*sin(theta+2*(pi/3)), radius/3);
	fractal_circle(x+radius*cos(theta+3*(pi/3)), y+radius*sin(theta+3*(pi/3)), radius/3);
	fractal_circle(x+radius*cos(theta+4*(pi/3)), y+radius*sin(theta+4*(pi/3)), radius/3);
	fractal_circle(x+radius*cos(theta+5*(pi/3)), y+radius*sin(theta+5*(pi/3)), radius/3);
}

void fractal_pentagon(int x, int y, int radius)						// recursive pentagon based on its center (x,y) and radius
{
	if( radius < 2 ) 	return;							// base case - radius too small

	double theta = pi/2;

	draw_pentagon(x, y, radius);							// draw one pentagon

	fractal_pentagon(x+radius*cos(theta+0*(2*pi/5)), y+radius*sin(theta+0*(2*pi/5)), radius/3);	// and five others branching off
	fractal_pentagon(x+radius*cos(theta+1*(2*pi/5)), y+radius*sin(theta+1*(2*pi/5)), radius/3);
	fractal_pentagon(x+radius*cos(theta+2*(2*pi/5)), y+radius*sin(theta+2*(2*pi/5)), radius/3);
	fractal_pentagon(x+radius*cos(theta+3*(2*pi/5)), y+radius*sin(theta+3*(2*pi/5)), radius/3);
	fractal_pentagon(x+radius*cos(theta+4*(2*pi/5)), y+radius*sin(theta+4*(2*pi/5)), radius/3);
}

void fractal_tree(int x, int y, int length, double angle)				// recursive tree based on its base (x,y) and length
{
	if( length < 2 ) 	return;							// base case
	
	gfx_line(x, y, x+length*cos(angle), y+length*sin(angle));			// we draw one line based on an angle

	fractal_tree(x+length*cos(angle), y+length*sin(angle), 2*length/3, (angle+pi/2)-pi/3);		// the straight line starts at -pi/2, so we must
	fractal_tree(x+length*cos(angle), y+length*sin(angle), 2*length/3, (angle+pi/2)-2*pi/3);	// treat this as zero so others branch out
}

void fractal_wheat(int x, int y, int length, double angle)				// recursive wheat (tree) based on its base (x,y) and length
{
	if( length < 2 ) 	return;							// base case

	gfx_line(x, y, x+length*cos(angle), y+length*sin(angle));			// we draw one line based on an angle

	fractal_wheat(x+(length/4)*cos(angle), y+(length/4)*sin(angle), 3*length/10, (angle+pi/2)-pi/3);	// then eight lines branch out
	fractal_wheat(x+(length/4)*cos(angle), y+(length/4)*sin(angle), 3*length/10, (angle+pi/2)-2*pi/3);	// (four pairs)
	
	fractal_wheat(x+(length/2)*cos(angle), y+(length/2)*sin(angle), 3*length/10, (angle+pi/2)-pi/3);	// each of the branches is a fraction
	fractal_wheat(x+(length/2)*cos(angle), y+(length/2)*sin(angle), 3*length/10, (angle+pi/2)-2*pi/3);	// of the length of its parent branch

	fractal_wheat(x+(3*length/4)*cos(angle), y+(3*length/4)*sin(angle), 3*length/10, (angle+pi/2)-pi/3);
	fractal_wheat(x+(3*length/4)*cos(angle), y+(3*length/4)*sin(angle), 3*length/10, (angle+pi/2)-2*pi/3);

	fractal_wheat(x+(length)*cos(angle), y+(length)*sin(angle), 3*length/10, (angle+pi/2)-pi/3);
	fractal_wheat(x+(length)*cos(angle), y+(length)*sin(angle), 3*length/10, (angle+pi/2)-2*pi/3);
}

void fractal_spiral(int x, int y, double radius, double angle)				// draw a spiral based on its center (x,y) and radius
{
	if( radius < 1 )								// base case
	{
		gfx_line(x,y,x,y);							// if our spiral is smaller than 1 pixel, it is a dot
		return;
	}

	while( radius > 1 )								// recursive spirals
	{
		fractal_spiral(x+radius*cos(angle), y+radius*sin(angle), radius/3, angle);
		
		radius *= .9;
		angle += .5;
	}
}

int main( void )
{
	int Xheight = 750;		// x axis of window
	int Yheight = 750;		// y axis of window

	int quit = 0;			// quitting boolean

	double pi = 3.14159;

	char user;

	gfx_open(Xheight, Yheight, "Fractal Generator");	// opening graphics window
	gfx_color(255, 255, 255);				// setting graphics color to white

	while( 1 )
	{
		user = gfx_wait();

		switch( user )
		{
			case '1':	// fractal triangle
			{
				gfx_clear();
				fractal_triangle((Xheight/2), Yheight-10, 10, 10, Xheight-10, 10);	// having the fractal take up nearly entire screen
				break;
			}
			case '2':	// fractal square
			{
				gfx_clear();
				fractal_square(Xheight/4, Yheight/4, 3*Xheight/4, Yheight/4, 3*Xheight/4, 3*Yheight/4, Xheight/4, 3*Yheight/4);
				break;
			}
			case '3':	// fractal square (spiral)
			{
				gfx_clear();
				fractal_squareSpiral(Xheight/2, Yheight/2, 9*Xheight/10, 0);
				break;
			}
			case '4':	// fractal circle
			{
				gfx_clear();
				fractal_circle(Xheight/2, Yheight/2, Xheight/4);
				break;
			}
			case '5':	// fractal pentagon
			{
				gfx_clear();
				fractal_pentagon(Xheight/2, Yheight/2, Xheight/3);
				break;
			}
			case '6':	// fractal tree
			{
				gfx_clear();
				fractal_tree(Xheight/2, Yheight, Yheight/3, -1*pi/2);
				break;
			} 
			case '7':	// fractal wheat
			{
				gfx_clear();
				fractal_wheat(Xheight/2, Yheight, 3*Yheight/5, -1*pi/2);
				break;
			}
			case '8':	// fractal spiral
			{
				gfx_clear();
				fractal_spiral(Xheight/2, Yheight/2, Xheight, 0);
				break;
			}
			case 'q':	// user quits
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
