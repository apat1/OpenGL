/*****************************************************************************
Andy Pat
CSE 470
September 25, 2013

Assignment 1
******************************************************************************/

#include <stdio.h>
#include <math.h>
#define PI 3.14159265

/* Include the GLUT library. This file (glut.h) contains gl.h and glu.h */
/* See how this is "glut.h" as opposed to <glut.h> - this is due to the fact that you need
   glut in your local directory. */
#include "glut.h"

/** Global Variables **/
// Variable to set mode to draw filled or outline shapes. Default is filled. 
int mode = 1; 
// Angle for rotations
double angle = 0;
// Variable for cannon angle (min 20 degrees, max 160 degrees)
double keyAngle = 90;
// Variables for cannon x translations 
double xTranslate = 0;


/*
   Function to draw a rectangle based on parameters width, height, and mode.
   If mode is 2, draw in outline. If mode is 1, draw in filled. 
   Mode is default 1. It can be changed with pop-up menu.  
   Starting point is the center of the square. 
*/
void drawRectangle(double width, double height)
{
	if(mode == 2)
	{
		// Draw an outline rectangle
		glBegin(GL_LINE_LOOP);
		glVertex2f(-(width/2), -(height/2));
		glVertex2f((width/2), -(height/2));
		glVertex2f((width/2), (height/2));
		glVertex2f(-(width/2), (height/2));
		glEnd();
	}
	else if(mode == 1)
	{
		// Draw a filled rectangle
		glBegin(GL_POLYGON);
		glVertex2f(-(width/2), -(height/2));
		glVertex2f((width/2), -(height/2));
		glVertex2f((width/2), (height/2));
		glVertex2f(-(width/2), (height/2));
		glEnd();
	}
}

/*
   Function to draw a circle based on parameters radius and mode.
   If mode is 2, draw in outline. If mode is 1, draw in filled. 
   Mode is default 1. It can be changed with pop-up menu. 
   Coordinate system is at center of the circle. 
*/
void drawCircle(double radius)
{
	if(mode == 2)
	{
		// Draw an outline circle
		glBegin(GL_LINE_LOOP);
		for(int i = 0; i <= 360; i++)
		{
			glVertex2f((cos((PI * i)/180)) * radius, (sin((PI * i)/180)) * radius);		 
		}
		glEnd();
	}
	else if(mode == 1)
	{
		// Draw a filled circle
		glBegin(GL_POLYGON);
		for(int i = 0; i <= 360; i++)
		{
			glVertex2f((cos((PI * i)/180)) * radius, (sin((PI * i)/180)) * radius);	  
		}
		glEnd();
	}
}

/*
   Function to draw a triangle based on three sets of points and mode.
   If mode is 2, draw in outline. If mode is 1, draw in filled. 
   Mode is default 1. It can be changed with pop-up menu. 
   (x1, y1); (x2, y2); (x3, y3) are the three points of the triangle,
   where (x1, y1) signifies the starting point. 
*/
void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	if(mode == 2)
	{
		// Draw an outline triangle
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glEnd();
	}
	else if(mode == 1)
	{
		// Draw a filled triangle
		glBegin(GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glEnd();
	}
}

/*
   Function to draw a star based on the inputed x and y.
   (x, y) is a set of points that represents the starting point.
   It is the upmost tip of the star. 
*/
void drawStar(double x, double y)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 0.2, y - 0.3);
	glVertex2f(x + 0.5, y - 0.3);
	glVertex2f(x + 0.3, y - 0.5);
	glVertex2f(x + 0.4, y - 0.85);
	glVertex2f(x, y - 0.65);
	glVertex2f(x - 0.4, y - 0.85);
	glVertex2f(x - 0.3, y - 0.5);
	glVertex2f(x - 0.5, y - 0.3);
	glVertex2f(x - 0.2, y - 0.3);
	glEnd();
}

/*
   Function to draw a keyhole based on the inputed x and y.
   (x, y) is a set of points that represents the starting point.
   It is the bottom left corner of the keyhole.  
*/
void drawKeyhole(double x, double y)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 0.4, y);
	glVertex2f(x + 0.3, y + 0.4);
	for(int i = 290; i <= 360; i++)
	{
		glVertex2f(((cos((PI * i)/180)) * 0.3) + x + 0.2, ((sin((PI * i)/180)) * 0.3) + y + 0.7);	  
	}
	for(int i = 0; i <= 250; i++)
	{
		glVertex2f(((cos((PI * i)/180)) * 0.3) + x + 0.2, ((sin((PI * i)/180)) * 0.3) + y + 0.7);	  
	}
	glEnd();
}

/*
	Assign actions based on pop-up menu selection
*/
void SelectFromMenu(int idCommand)
{
	switch(idCommand)
    {
		case 1:
			// draw solid shapes
			mode = 1;
			break;

		case 2:
			// draw outline shapes
			mode = 2;
			break;     

		case 3:
			// reset game
			break;

		case 4:
			// exit
			exit (0);
			break;
    }

	// Redraw after menu selection
	glutPostRedisplay();
}

/*
	Create pop-up menu that comes up with right-mouse click
*/
void BuildPopupMenu(void)
{
	int sub;
	int menu;

	// Create the submenu for Polygons
	sub = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("Filled", 1);
	glutAddMenuEntry("Wire", 2);

	// Create the main menu 
	menu = glutCreateMenu(SelectFromMenu);
	glutAddSubMenu ("Polygons", sub); // Add the item entries in the "sub" menu as a submenu of "Polygons"
	glutAddMenuEntry ("Reset", 3);
	glutAddMenuEntry ("Quit", 4);

	// Menu will pop up with right mouse click
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/*
	Function to handle spacebar pressed. 
*/
void spacebar(unsigned char key, int x, int y) 
{
	// Checks if key hit is ASCII 32 (spacebar)
	if(key == 32)
	{

	}
}

/*
	Function to handle arrow keys
*/ 
void specialKeys(int key, int x, int y)
{
	switch(key)
    {
		case GLUT_KEY_DOWN:
			// cannon rotate right
			if(keyAngle > 20)
			{
				keyAngle -= 4;
			}
			break;

		case GLUT_KEY_UP:
			// cannon rotate left
			if(keyAngle < 160)
			{
				keyAngle += 4;
			}
			break;     

		case GLUT_KEY_LEFT:
			// cannon move left
			if(xTranslate > -15)
			{
				xTranslate -= 0.5;
			}
			break;

		case GLUT_KEY_RIGHT:
			// cannon move right
			if(xTranslate < 15)
			{
				xTranslate += 0.5; 
			}
			break;
    }

	// Redraw after menu selection
	glutPostRedisplay();
}

/* 
 * The rountine display() gets called each time the window is redrawn.
 */
void display()
{
	/* set background clear color to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT);

	// resets drawing location after resize
	glLoadIdentity();

	// translation
	glTranslatef(0, 0, -20); 

	glPushMatrix();
		// set color to white before drawing keyhole
		glColor3f(1.0, 1.0, 1.0);
		drawKeyhole(0, 0);
		glPushMatrix();
			// set color to yellow before drawing 
			glColor3f(1.0, 1.0, 0.0);
			// rotate in XY plane
			glRotatef(360 - angle, 0, 0, 1);
			// translation
			glTranslatef(0, 4, 0);
			drawRectangle(1, 1);
			glPushMatrix();
				// rotate clockwise in XY plane
				glRotatef(angle, 0, 0, 1);
				// translation
				glTranslatef(0, 2, 0);
				drawStar(0, 0);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			// set color to yellow before drawing 
			glColor3f(1.0, 1.0, 0.0);
			// rotate in XY plane
			glRotatef(360 - angle, 0, 0, 1);
			// translation
			glTranslatef(0, -4, 0);
			drawRectangle(1, 1);
			glPushMatrix();
				// rotate clockwise in XY plane
				glRotatef(angle, 0, 0, 1);
				// translation
				glTranslatef(0, 2, 0);
				drawStar(0, 0);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			// set color to red
			glColor3f(1.0, 0.0, 0.0);
			glRotatef(360 - angle, 0, 0, 1);
			// translation
			glTranslatef(2, 0, -5);
			drawTriangle(1, 0, 2, 3, 3, 2);
		glPopMatrix();
		glPushMatrix();
			// set color to green
			glColor3f(0.0, 1.0, 0.0);
			glRotatef(360 - angle, 0, 0, 1);
			// translation
			glTranslatef(-2, 0, -5);
			drawTriangle(-1, 0, -2, -3, -3, -2);
		glPopMatrix();
/////////////////////////////////////////////////////////
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(0, 8, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-1, 7.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-2, 7, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-3, 6.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-4, 6, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-5, 5.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-6, 5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-5, -5.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-4, -6, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-3, -6.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-2, -7, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-1, -7.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to blue
			glColor3f(0.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(0, -8, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
/////////////////////////////////////////////////////////
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(1, 8, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(2, 7.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(3, 7, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(4, 6.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(5, 6, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(6, 5.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(7, 5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(6, -5.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(5, -6, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(4, -6.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(3, -7, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(2, -7.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to purple
			glColor3f(1.0, 0.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(1, -8, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
//////////////////////////////////////////////////////////
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, 4.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, 3.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, 2.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, 1.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, 0.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, -0.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, -1.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, -2.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, -3.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(8, -4.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(7, -5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
//////////////////////////////////////////////////////////
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, 4.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, 3.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, 2.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, 1.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, 0.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, -0.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, -1.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, -2.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, -3.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-7, -4.5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
		glPushMatrix();
			// set color to cyan
			glColor3f(0.0, 1.0, 1.0);
			// rotate clockwise in XY plane
			glRotatef(angle, 0, 0, 1);
			// translation
			glTranslatef(-6, -5, 0);
			drawRectangle(0.5, 0.5);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		// set color to red
		glColor3f(1.0, 0.0, 0.0);
		// translation
		glTranslatef(13, 9, 0);
		drawCircle(0.5);
	glPopMatrix();

	glPushMatrix();
		// set color to green
		glColor3f(0.0, 1.0, 0.0);
		// translation 
		glTranslatef(-13, 9, 0);
		drawCircle(0.5);
	glPopMatrix();

	// Cannon/Paddle
	glPushMatrix();
		// set color to white before drawing cannon
		glColor3f(1.0, 1.0, 1.0);
		// translation
		glTranslatef(xTranslate, -15, 0); 
		glRotatef(keyAngle, 0, 0, 1);
		drawRectangle(0.5, 0.2);
		glPushMatrix();
	glPopMatrix();


	// for double buffers
	glutSwapBuffers();

	// increment the angle to rotate
	angle += .03; 
	// reset angle to 0 if greater than 360
	if(angle > 360)
	{
		angle = 0;
	}

	/* ready to draw now! forces buffered OGL commands to execute */
	glFlush();
}

/* 
 * The rountine refresh gets called each time the window is resized.
 */
void refresh(int width, int height)
{
	// width and height gotten from glut
	// viewport setting at (0, 0) for bottom-left of window
	// and (width, height) for top-right of window
	glViewport(0, 100, (GLsizei)width, (GLsizei)height);


	/* identify the projection matrix that we would like to alter */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// setting angle and ratio
	gluPerspective(80, (GLfloat)width / (GLfloat)height, 1, 500); 

	/* identify the modeling and viewing matrix that can be modified from here on */
	/* we leave the routine in this mode in case we want to move the object around */
	/* or specify the camera */
	glMatrixMode(GL_MODELVIEW);
}

/* The main program */

int main(int argc, char** argv)
{

	/* create a window, position it, and name it */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double buffering
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Project 1 - Andy Pat");

	/* create a callback routine for (re-)display */
	glutDisplayFunc(display);

	// Idle function will use display
	glutIdleFunc(display);

	// Create our popup menu
	BuildPopupMenu();

	// Reshape the window after resizing window
	glutReshapeFunc(refresh);

	// Add functionality for keyboard interaction
	glutKeyboardFunc(spacebar); 
	glutSpecialFunc(specialKeys);

	/* entering the event loop */
	glutMainLoop();

	/* code here will not be executed */
}

