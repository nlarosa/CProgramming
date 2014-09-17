// CSE 20211
//
// This program involves the user controlling a ball that must avoid
// "civilians" that are moving in random circular patterns
//
// Nicholas LaRosa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "gfx.h"

int main(void)			// we will create a game where the user drives a car and has to avoid civilians
{
	int screenX = 900;
	int screenY = 900;

	float x;
	float y;

	float x1;		// point 1
	float y1;

	float x2;		// point 2
	float y2;

	// car variables

	float carX = 450;	// center of the car coordinates
	float carY = 800;
	float radiusC = 20;	// radius of the car
	float inc = 25;		// speed increment for car

	float carMin = -200;	// min and max velocity in pixels/sec
	float carMax = 200;

	float vx = 10;		// velocity of the car
	float vy = 10;

	float deltaT = 0.01;    // change in time between each frame (in seconds)
	float pi = atan(1)*4;   // constant for pi

	char user;              // this will be the value of the user input
	int random;		// a random number	

	int stop = 0;		// boolean for pausing our program
	int quit = 0;		// boolean for stopping our program

	// civilian variables

	float radiusM;		// radius of the civilian motion
	float radiusD = 10;	// radius of the civilian (circle)
	int min = 50;		// min and max for civilian motion
	int max = 200;
	int sign;		// integer for controlling  the direction of civilians
	int speed;		// integer for controlling the speed of civilians

	int c = 0;		// counter for loops
	int moveC = 0;		// counters for drawing and movie the civilians
	int drawC;	
	int civilians = 5;	// number of civilians

	srand(time(NULL));

	// coordinates for the civilian centers of motion

	int civilian[10][10];		// one row for every civilian (extra rows are for more civilians if necessary)

	civilian[1][1] = 250;					// civilian 1, x and y coordinates
	civilian[1][2] = 250;					
	civilian[1][3] = min + (rand()%(max-min+1)); 		// random circular path radius
	civilian[1][4] = -1;					// controls the direction of the motion
	civilian[1][5] = 1;					// each civilian has speed constant
	civilian[1][6] = 0;					// keeps track of the angle position of the civilian

	civilian[2][1] = 250;
	civilian[2][2] = 900 - 250;
	civilian[2][3] = min + (rand()%(max-min+1)); 
	civilian[2][4] = 1;
	civilian[2][5] = 2;					
	civilian[2][6] = 0;

	civilian[3][1] = 450;
	civilian[3][2] = 450;
	civilian[3][3] = min + (rand()%(max-min+1));
	civilian[3][4] = -1;
	civilian[3][5] = 1;
	civilian[3][6] = 0;

	civilian[4][1] = 900 - 250;	
	civilian[4][2] = 250;
	civilian[4][3] = min + (rand()%(max-min+1)); 	
	civilian[4][4] = 1;
	civilian[4][5] = 2;
	civilian[4][6] = 0;

	civilian[5][1] = 900 -250;
	civilian[5][2] = 900 -250;
	civilian[5][3] = min + (rand()%(max-min+1));
	civilian[5][4] = -1;
	civilian[5][5] = 1;
	civilian[5][6] = 0;

	screenX = 900;
	screenY = 900;

	gfx_open(screenX, screenY, "Road Rage!");

	gfx_clear_color(255, 255, 255);		// change the background color to white
	gfx_clear();

	gfx_color(0, 0, 0);			// change color to white for the circles

	while( 1 )
	{
		gfx_clear();	

		if( gfx_event_waiting() )			// we will wait until the user presses a button
		{
			user = gfx_wait();			// user input stored

			switch( user )
			{
				case '1':		// civilian speed stage 1
					{
						for( c = 1; c <= civilians; c++ )
						{
							random = 1+(rand()%6);		// random int between 1 and 6
							civilian[c][5] = random;
						}

						carX = 450;       // reset car coordinates
        					carY = 800;
						vx = 10;
						vy = 10;

						break;
					}
				case '2':		// civilian speed stage 2
					{
						for( c = 1; c <= civilians; c++ )
						{
							random = 1+(rand()%6);		// random int between 1 and 6
							civilian[c][5] = random;
						}

						carX = 450;       // reset car coordinates
                                                carY = 800;
                                                vx = 10;
                                                vy = 10;

						break;
					}			
				case '3':		// civilian speed stage 3
					{
						for( c = 1; c <= civilians; c++ )
						{
							random = 1+(rand()%6);		// random int between 1 and 6
							civilian[c][5] = random;
						}

						carX = 450;       // reset car coordinates
                                                carY = 800;
                                                vx = 10;
                                                vy = 10;

						break;
					}	
				case '4':		// civilian speed stage 4
					{
						for( c = 1; c <= civilians; c++ )
						{
							random = 1+(rand()%6);		// random int between 1 and 6
							civilian[c][5] = random;
						}

						carX = 450;       // reset car coordinates
                                                carY = 800;
                                                vx = 10;
                                                vy = 10;

						break;
					}
				case '5':		// civilian speed stage 5
					{
						for( c = 1; c <= civilians; c++ )
						{
							random = 1+(rand()%6);		// random int between 1 and 6
							civilian[c][5] = random;
						}

						carX = 450;       // reset car coordinates
                                                carY = 800;
                                                vx = 10;
                                                vy = 10;

						break;
					}
				case 'w':		// decrease vy (towards top)
					{
						if( vy > carMin )		// subtract 1 from vy as long as it is greater than -20
						{
							vy -= inc;		
						}
					
						if( gfx_event_waiting() )	// allows multiple keyboard buttons
						{
							user = gfx_wait();	
							
							switch( user )
							{
								case 'a':
								{
									if( vx > carMin )   
                                                			{
                                                       	 			vx -= inc;
                                                			}
                                               		 		break;
								}
								case 'd':
								{
									if( vx < carMax )   
                                                			{
                                                        			vx += inc;
                                                			}
                                               	 			break;
								}
								case 's':
								{
									if( vy < carMax )  
                                                			{
                                                        			vy += inc;
                                                			}
                                               				break;	
								}
							}
						}
						break;
					}
				case 'a':		// decrease vx (towards left)
					{
						if( vx > carMin )		// subtract 1 from vx as long as it is greater than -20
						{
							vx -= inc;
						}
						
						if( gfx_event_waiting() )	// allows for multiple keyboard buttons
                                                {
                                                        user = gfx_wait();

                                                        switch( user )
                                                        {
                                                                case 'w':
                                                                {
                                                                        if( vy > carMin )     
                                                                        {
                                                                                vy -= inc;
                                                                        }
                                                                        break;
                                                                }
                                                                case 'd':
                                                                {
                                                                        if( vx < carMax )    
                                                                        {
                                                                                vx += inc;
                                                                        }
                                                                        break;
                                                                }
                                                                case 's':
                                                                {
                                                                        if( vy < carMax )   
                                                                        {
                                                                                vy += inc;
                                                                        }
                                                                      	break;
                                                                }
                                                        }
                                                }

						break;
					}
				case 'd':		// increase vx (towards right)
					{
						if( vx < carMax )
						{
							vx += inc;		// add 1 to vx as long as it is less than 20
						}
	
						if( gfx_event_waiting() )	// allows for multiple keyboard buttons
                                                {
                                                        user = gfx_wait();

                                                        switch( user )
                                                        {
                                                                case 'w':
                                                                {
                                                                        if( vy > carMin )   
                                                                        {
                                                                                vy -= inc;
                                                                        }
                                                                        break;
                                                                }
                                                                case 'a':
                                                                {
                                                                        if( vx > carMin )  
                                                                        {
                                                                                vx -= inc;
                                                                        }
                                                                        break;
                                                                }
                                                                case 's':
                                                                {
                                                                        if( vy < carMax ) 
                                                                        {
                                                                                vy += inc;
                                                                        }
                                                                        break;
                                                                }
                                                        }
                                                }
						break;
					}
				case 's': 		// increase vy (towards bottom)
					{
						if( vy < carMax )
						{
							vy += inc;		// add 1 to vy as long as it is less than 20
						}

						if( gfx_event_waiting() )		// allows for multiple keyboard buttons
                                                {
                                                        user = gfx_wait();

                                                        switch( user )
                                                        {
                                                                case 'w':
                                                                {
                                                                        if( vy > carMin )       
                                                                        {
                                                                                vy -= inc;
                                                                        }
                                                                        break;
                                                                }
                                                                case 'a':
                                                                {
                                                                        if( vx > carMin )      
                                                                        {
                                                                                vx -= inc;
                                                                        }
                                                                        break;
                                                                }
                                                                case 'd':
                                                                {
                                                                        if( vx < carMax )     
                                                                        {
                                                                                vx += inc;
                                                                        }
                                                                        break;
                                                                }
                                                        }
                                                }
						break;
					}
				case 'q':		// quit the game (anytime)	
					{
						quit = 1;
						break;
					}
			}
		}

		for( c = 1; c <= civilians; c++ )
		{
			radiusM = civilian[c][3];		// retrieve the radius for each civilian
			sign = civilian[c][4];			// retrieve the direction of motion also
			speed = civilian[c][5];

			civilian[c][6] += speed;		// each civilian has an angle measurment
			moveC = civilian[c][6];

			x = civilian[c][1] + (cos(moveC*pi/180)*radiusM);
			y = civilian[c][2] + sign*(sin(moveC*pi/180)*radiusM);
			
			if( (x >= (carX-radiusC)) && (x <= (carX+radiusC)) && (y >= (carY-radiusC)) && (y <= (carY+radiusC)) )	// a civilian is hit!
			{
				quit = 1;
				break;				// we hit a civilian!
			}

			x2 = x + radiusD;
			y2 = y;

			for( drawC = 0; drawC <= 360; drawC++ )
			{
				x1 = x2;
				y1 = y2;

				x2 = x + (cos(drawC*pi/180)*radiusD);        	// draw the circle point by point
				y2 = y + (sin(drawC*pi/180)*radiusD);	

				gfx_line(x1, y1, x2, y2);
			}
		}

		if( quit == 1 )			// exit the program, we hit a civilian!
		{
			usleep(1000000);	// pause before exiting
			break;
		}

		// done drawing civilians, now we should draw the car

		if( (carX < radiusC) || ((carX + radiusC) > screenX) )
		{
			vx *= -1;                	 	// if the new plot is going to be out of range then we need to "bounce"
		}
		if( (carY < radiusC) || ((carY + radiusC) > screenY) )
		{
			vy *= -1;                 		// if the new plot is going to be out of range then we need to stop the car
		}	

		carX = carX + vx*deltaT;
		carY = carY + vy*deltaT;

		x2 = carX + radiusC;
		y2 = carY;

		for( drawC = 0; drawC <= 360; drawC++ )				// draw our car point by point
		{
			x1 = x2;
			y1 = y2;

			x2 = carX + (cos(drawC*pi/180)*radiusC);
			y2 = carY + (sin(drawC*pi/180)*radiusC);

			gfx_line(x1, y1, x2, y2);				// double line (bold)
			gfx_line(x1-1, y1-1, x2-1, y2-1);
		}

		gfx_flush();
		usleep(10000);				// pause for a millisecond
	}
}


