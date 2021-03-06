#include <windows.h> // use as needed for your system
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <iostream>
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
#include <math.h>

using namespace std;

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
    glPointSize(2.0); // a ‘dot’ is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 320, -50, 240);
}

const float hexagon_r=20;
const float hexagon_dx=hexagon_r*cos(30.0*M_PI/180.0);
const float hexagon_dy=hexagon_r*sin(30.0*M_PI/180.0);
void draw_hexagon(float x,float y)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x-hexagon_dx,y-hexagon_dy);
    glVertex2f(x-hexagon_dx,y+hexagon_dy);
    glVertex2f(x,y+hexagon_r);
    glVertex2f(x+hexagon_dx,y+hexagon_dy);
    glVertex2f(x+hexagon_dx,y-hexagon_dy);
    glVertex2f(x,y-hexagon_r);
    glEnd();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    /*for(int row = 0 ; row < 6 ; row++)
    {
        glPushMatrix();
        for(int col = 0 ; col < 6 ; col++)
        {
            draw_hexagon(0,0);
            glTranslatef(sqrt(3) * hexagon_r,0,0);
        }
        glPopMatrix();
        glTranslatef( sqrt(3)/2 * hexagon_r, sqrt(3) * hexagon_r-4 ,0);
    }*/
    draw_hexagon(0,0);
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Hexagonal Tiling"); // open the screen window
    glutDisplayFunc(myDisplay); // register redraw function
    myInit();
    glutMainLoop(); // go into a perpetual loop
    return EXIT_SUCCESS;
}
